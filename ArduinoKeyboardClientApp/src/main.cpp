#include <iostream>
#include <stdio.h>

#include "COM/COMPort.h"

#include "UI/ClientApp.h"

int main() {
	/*
	auto ports = COMPort::scanForPorts();
	if (ports.scanStatus != ERROR_SUCCESS) {
		fprintf(stderr, "Error occured while scanning\n");
		exit(1);
	}
	for (const auto& i : ports.portIDs) {
		printf("%i\n", i);
	}

	COMPort::COMPort port(ports.portIDs[0]);
	port.onMessageReceived([](std::string msg) {
		printf("Message: %s\n", msg.data());
		});

	auto status = port.open();

	printf("hey");

	if (status != COMPort::COMStatus::OK) {
		printf("Error while opening\n");
		printf("%i\n", status);
	}
	*/
	Global::initGlobals();

	App::App app;
	app.buildUI();
	app.startLoop();

	Global::freeGlobals();

	return 0;
}
