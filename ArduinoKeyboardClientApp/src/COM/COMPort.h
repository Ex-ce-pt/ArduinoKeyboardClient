#pragma once

#include <vector>
#include <string>
#include <thread>
#include <functional>

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
		using MessageCallback = std::function<void(std::string)>;

	private:
		ULONG portID;
		DCB dcb;
		HANDLE hCom;
		std::unique_ptr<std::thread> listener;
		std::atomic_bool listenerRunning;
		MessageCallback cb;

		COMStatus configurePort();
		void startListenerThread();

	public:
		COMPort();
		COMPort(ULONG portID);
		~COMPort();

		COMStatus open();
		void close();

		void onMessageReceived(MessageCallback cb);

		void setPortID(ULONG portID);

		ULONG getPortID() const;
		HANDLE getCOMHandle() const;
		bool isListenerRunning() const;
		MessageCallback getOnMessageReceivedCallback() const;
	};

	PortScanStatus scanForPorts();

}
