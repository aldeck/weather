/*
 * Copyright 2012, Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alexandre.deckner@uzzl.com>
 */


#include "App.h"

#include <Alert.h>

#include "MainWindow.h"


App::App()
	:
	BApplication("application/x-vnd.Haiku-Weather")
{
	BRect frame(50, 50, 640 + 50, 480 + 50);
	const char *title = "Weather";
	fMainWindow = new MainWindow(frame, title);
}


App::~App()
{
}


void App::AboutRequested()
{
	BAlert* alert;
	alert = new BAlert("About", "Weather", "ok");
	alert->Go(NULL);
}


void App::MessageReceived(BMessage *message)
{
}


int
main(int argc, char** argv)
{
	App app;
	app.Run();
	return 0;
}
