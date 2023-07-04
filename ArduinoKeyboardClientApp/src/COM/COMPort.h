#pragma once

#include <vector>
#include <string>
#include <thread>

#define NOMINMAX
#include <Windows.h>

namespace COMPort {

	struct PortScanStatus {
		std::vector<ULONG> portIDs;
		ULONG scanStatus;
	};

	enum class COMStatus {
		OK,
		INVALID_HANDLE,
		ACCESS_DENIED,
		GET_STATE_FAIL,
		SET_STATE_FAIL,
		SET_MASK_FAIL
	};

	class COMPort {
	private:
		using MessageCallback = void(*)(std::string);

	private:
		ULONG portID;
		DCB dcb;
		HANDLE hCom;
		std::thread* listener;
		bool listenerRunning;
		MessageCallback cb;

		COMStatus configurePort();
		void startListenerThread();

	public:
		COMPort(ULONG portID);
		~COMPort();

		COMStatus open();

		void onMessageReceived(MessageCallback cb);

		HANDLE getCOMHandle() const;
		bool isListenerRunning() const;
		MessageCallback getOnMessageReceivedCallback() const;
	};

	PortScanStatus scanForPorts();

}
