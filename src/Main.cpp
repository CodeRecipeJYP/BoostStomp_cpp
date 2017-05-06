/*
 BoostStomp - a STOMP (Simple Text Oriented Messaging Protocol) client
----------------------------------------------------
Copyright (c) 2012 Elias Karakoulakis <elias.karakoulakis@gmail.com>

SOFTWARE NOTICE AND LICENSE

BoostStomp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

BoostStomp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with BoostStomp .  If not, see <http://www.gnu.org/licenses/>.

for more information on the LGPL, see:
http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License
*/

// 
// Main.cpp: a demo STOMP client
// (c) 2011 Elias Karakoulakis <elias.karakoulakis@gmail.com>
//

#include <string>
#include <sstream>
#include <iostream>
#include "unistd.h"

#include "BoostStomp.hpp"

using namespace STOMP;
using namespace std;

static BoostStomp*  stomp_client;
static string       notifications_receive_topic = "/topic/command/general";
static string       notifications_send_topic = "/app/general/command";

// -------------------------------------------------------
// a callback for any STOMP Frames in subscribed channels
// -------------------------------------------------------
bool subscription_callback(STOMP::Frame& _frame) {
	cout << "--Incoming STOMP Frame--" << endl;
	cout << "  Headers:" << endl;
	hdrmap headers = _frame.headers();
	for (STOMP::hdrmap::iterator it = headers.begin() ; it != headers.end(); it++ )
	    cout << "\t" << (*it).first << "\t=>\t" << (*it).second << endl;
	//
	cout << "  Body: (size: " << _frame.body().v.size() << " chars):" << endl;
	hexdump(_frame.body().c_str(), _frame.body().v.size() );
	return(true); // return false if we want to disacknowledge the frame (send NACK instead of ACK)
}

// -----------------------------------------
int main(int argc, char *argv[]) {
// -----------------------------------------
    string  stomp_host = "52.78.111.146";
    int     stomp_port = 80;

    cout << "Start!!@#!#$@$#!@" << endl;

    try {
    	// initiate a new BoostStomp client
        stomp_client = new BoostStomp(stomp_host, stomp_port);

        // start the client, (by connecting to the STOMP server)
        stomp_client->start();

        // subscribe to a channel
//        stomp_client->subscribe(notifications_send_topic, (STOMP::pfnOnStompMessage_t) &subscription_callback);
//        stomp_client->subscribe(notifications_receive_topic, (STOMP::pfnOnStompMessage_t) &subscription_callback);
//
//        // construct a headermap
        STOMP::hdrmap headers;
        headers["simpMessageType"] = string("MESSAGE");
        headers["stompCommand"] = string("SEND");
////        headers["header3"] = string("value3");
        string body = string("this is the FIRST message body.");
//
//        // add an outgoing message to the queue
        stomp_client->send(notifications_send_topic, headers, body);
//
//        // send another one right away
//        binbody bb;
//        bb << "this is the SECOND message.";
//        bb << '\0';
//        bb << "with a NULL in it.";
//        string body2 = string("this is the SECOND message.");
//        stomp_client->send(notifications_send_topic, headers, bb);
//        sleep(1);
//        // add some more binary content in the body
//        binbody bb2;
//        bb2 << "this is the THIRD message.";
//        bb2 << '\0';
//        bb2 << "with";
//        bb2 << '\0';
//        bb2 << "TWO NULLs in it.";
//        stomp_client->send(notifications_send_topic, headers, bb2);
//        sleep(2);
//        // now some stress test (100 frames)
//        STOMP::hdrmap headers2;
//        for (int i = 0;  i < 100; i++) {
//        	cout << "Sending stress frame " << i << endl;
//        	headers2["count"] = to_string<int>(i);
//        	stomp_client->send(notifications_send_topic, headers2, "");
//        };
        sleep(20);
        stomp_client->stop();
        delete stomp_client;
    } 
    catch (std::exception& e)
    {
        cerr << "Error in BoostStomp: " << e.what() << "\n";
        return 1;
    } 
    
    return 0;
}
