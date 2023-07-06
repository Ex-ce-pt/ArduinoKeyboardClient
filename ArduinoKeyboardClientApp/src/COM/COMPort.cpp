#include "COMPort.h"

#include <sstream>

#include <iostream>

static void readCOMBufferIndefinitely(COMPort::COMPort* self) {
	DWORD dwEvtMask = 0;

	if (WaitCommEvent(self->getCOMHandle(), &dwEvtMask, NULL)) {
		char chRead;
		DWORD dwRead;
		std::stringstream ss;
		do {
			if (!self->isListenerRunning()) {
				return;
			}

			if (ReadFile(self->getCOMHandle(), &chRead, 1, &dwRead, NULL)) {
				if (dwRead != 0) {
					ss << chRead;

					if (chRead == '\n') {
						std::string msg;
						ss >> msg;
						if (self->getOnMessageReceivedCallback() != NULL)
							self->getOnMessageReceivedCallback()(msg);
					}
				}
			}
			else {
				fprintf(stderr, "ErrorReadFile.\n");
				break;
			}
		} while (dwRead);
	}
	else {
		DWORD dwRet = GetLastError();
		if (ERROR_IO_PENDING == dwRet) {
			printf("I/O is pending...\n");

		}
		else
			fprintf(stderr, "Wait failed with error %d.\n", GetLastError());
	}
}

COMPort::PortScanStatus COMPort::scanForPorts() {
	const size_t MAX_PORTS = 64;
	ULONG ports[MAX_PORTS] = { 0 };
	ULONG portsFound;
	auto status = GetCommPorts(ports, MAX_PORTS, &portsFound);

	std::vector<ULONG> portsVec;
	for (size_t i = 0; i < portsFound; i++) portsVec.push_back(ports[i]);

	return { portsVec, status };
}

COMPort::COMPort::COMPort()
: portID(NULL), dcb({}), hCom(NULL), listener(NULL), listenerRunning(false), cb(NULL)
{}

COMPort::COMPort::COMPort(ULONG portID)
	: COMPort()
{
	this->portID = portID;
}

COMPort::COMPort::~COMPort() {
	close();
}

COMPort::COMStatus COMPort::COMPort::configurePort() {
	BOOL fSuccess;

	std::wstring portName = L"COM" + std::to_wstring(portID);

	hCom = CreateFile(portName.data(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hCom == INVALID_HANDLE_VALUE) {
		if (GetLastError() == 5) return COMStatus::ACCESS_DENIED;
		return COMStatus::INVALID_HANDLE;
	}

	SecureZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	fSuccess = GetCommState(hCom, &dcb);

	if (!fSuccess) {
		return COMStatus::GET_STATE_FAIL;
	}

	dcb.BaudRate = CBR_115200;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	dcb.DCBlength = sizeof(dcb);

	if (!SetCommState(hCom, &dcb)) {
		return COMStatus::SET_STATE_FAIL;
	}

	printf("\nBaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d\n",
		dcb.BaudRate,
		dcb.ByteSize,
		dcb.Parity,
		dcb.StopBits);

	if (!SetCommMask(hCom, EV_RXCHAR)) {
		return COMStatus::SET_MASK_FAIL;
	}

	return COMStatus::OK;
}

void COMPort::COMPort::startListenerThread() {
	listenerRunning = true;
	listener = new std::thread(readCOMBufferIndefinitely, this);
}

COMPort::COMStatus COMPort::COMPort::open() {
	COMStatus status;
	
	status = configurePort();

	if (status != COMStatus::OK) {
		return status;
	}

	startListenerThread();

	return COMStatus::OK;
}

void COMPort::COMPort::close() {
	if (!listenerRunning) return;

	listenerRunning = false;

	if (listener != NULL) {
		listener->join();
		delete listener;
	}

	if (hCom != NULL) {
		CloseHandle(hCom);
	}
}

void COMPort::COMPort::onMessageReceived(MessageCallback cb) {
	this->cb = cb;
}

void COMPort::COMPort::setPortID(ULONG portID) {
	if (listenerRunning) return;

	this->portID = portID;
}

ULONG COMPort::COMPort::getPortID() const {
	return portID;
}

HANDLE COMPort::COMPort::getCOMHandle() const {
	return hCom;
}

bool COMPort::COMPort::isListenerRunning() const {
	return listenerRunning;
}

COMPort::COMPort::MessageCallback COMPort::COMPort::getOnMessageReceivedCallback() const {
	return cb;
}
