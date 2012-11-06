/*
 * Copyright 2012, Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alexandre.deckner@uzzl.com>
 */
#ifndef _MAINVIEW_H
#define _MAINVIEW_H


#include <String.h>
#include <UrlProtocolListener.h>
#include <View.h>


class NetListener : public BUrlProtocolListener {
public:
	virtual void					ResponseStarted(BUrlProtocol* caller);
	virtual void					DataReceived(BUrlProtocol* caller,
										const char* data, ssize_t size);
	virtual void					RequestCompleted(BUrlProtocol* caller, 
										bool success);
private:
	BString							fResponse;
};


class MainView : public BView {
public:
					MainView(BRect frame);
					~MainView();
	virtual void	Draw(BRect updateRect);
	virtual void	AttachedToWindow();
	virtual void	FrameResized(float width, float height);
};


#endif	// _MAINVIEW_H
