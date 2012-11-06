/*
 * Copyright 2012, Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alexandre.deckner@uzzl.com>
 */


#include "MainView.h"

#include "mdsplib/include/metar.h"

#include <Url.h>
#include <UrlRequest.h>

#include <stdio.h>


MainView::MainView(BRect frame)
	:
	BView(frame, "MainView", B_FOLLOW_ALL, B_WILL_DRAW)
{
}


MainView::~MainView()
{
}


void
MainView::AttachedToWindow()
{
	BView::AttachedToWindow();

	BString station("EDDL");
	BString urlString("https://www.aviationweather.gov/adds/metars/");
	urlString << "?station_ids=" << station << "&std_trans=standard&chk_metars=on";
	urlString << "&hoursStr=most+recent+only&submitmet=Submit";
	BUrlRequest* request = new BUrlRequest(BUrl(urlString), new NetListener());
	status_t err = request->Perform();
	printf("err %u\n", err);
}

//////////////
void
NetListener::ResponseStarted(BUrlProtocol* /*caller*/)
{
	fResponse = "";
}

void
NetListener::DataReceived(BUrlProtocol* caller,
	const char* data, ssize_t size)
{
	char* buf = new char[size+1];
	memcpy(buf, data, size);
	buf[size] = '\0';
	//printf("DataReceived\n%s\n", buf);
	fResponse << buf;	
}

void
NetListener::RequestCompleted(BUrlProtocol* caller, 
	bool success)
{
	printf("RequestCompleted\n%s\n", fResponse.String());
	BString station(">EDDL");
	int32 begin = fResponse.FindFirst(station);
	BString metar;
	if (begin != B_ERROR) {
		int32 end = fResponse.FindFirst("</", begin);
		if (end != B_ERROR) {
			fResponse.CopyInto(metar, begin + 1, end - begin - 1);
		}
	}
	
	printf("\nMETAR:\n%s\n", metar.String());
	Decoded_METAR dmetar;
	Decoded_METAR *Mptr = &dmetar;
	char* buf = new char[metar.Length()+1];
	memcpy(buf, metar.String(), metar.Length());
	buf[metar.Length()] = '\0';
	int err = DcdMETAR(buf, Mptr);
	printf("Decoding METAR status = %i\n", err);
	
	prtDMETR( Mptr );
}
/////////////


void
MainView::Draw(BRect updateRect)
{
	StrokeLine(BPoint(0,0), BPoint(100,100));
}


void
MainView::FrameResized(float width, float height)
{
}
