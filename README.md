house
=====

House code uses a Spark Core and a relay to trigger the buzzer on a door. The server is written in Node.js, and I'm running it on a DigitalOcean droplet, although you can run it on any machine with a static public IP address.

server
------

To set up the server:

1. First you'll need a server with a static public IP address. I used a DigitalOcean droplet, because it's only $5 / month, is easy to set up, and provides a static IP address.
2. On your server, clone this repository:

		git clone https://github.com/benkroop/house.git

3. Generate a TOTP private key. I recommend using an online (browser-based, JavaScript) generator, like [this one](http://blog.tinisles.com/2011/10/google-authenticator-one-time-password-algorithm-in-javascript/ "TOTP Generator"). 
4. Save the QR code for later, then update the "key" variable in server.js with your secret key.
5. run:

		node server.js

6. Open Google Authenticator on your phone, and scan the QR code that was generated when you created your key.
7. If your server is running, you should see the number "0" when you request '/' from your server's IP address.

Next, set up a Twilio phone number

1. Acquire a Twilio phone number. 
2. Go to https://www.twilio.com/user/account/phone-numbers/
3. Click the phone number you want to use as the house number.
4. Under SMS & MMS, set the request url to http://123.104.255.255/sms (Using your server's IP address), and select HTTP GET.

firmware
--------

To configure the firmware, update request.ip on line 68 in doorbell.ino to your server's IP address, using commas to separate each byte of the address separated by a comma. 

	request.ip = {123, 101, 255, 0}

Then flash the firmware onto the Spark Core.

hardware
--------

**This is the box that came with my apartment:**

![Front](/circuit/outside.jpg)

Connect the control side of a 3.3v relay to D7 of the Spark Core and to ground. On the contactor side of the relay, connect jumper wire, and solder the ends of the jumper wire either side of the button that controls your building's door buzzer. This allows the relay to jump the unlock button on your buzzer pannel. 

You'll need a 3.3v power supply or 5v MicroUSB source to power the Spark Core. I recommend drilling a hole your doorbell control box and running the USB cable into it to keep your wall looking clean. 

![Schematic](/circuit/schematic.png)

**Here's what that looks like inside the box:**

![Boards](/circuit/Boards+Relay.jpg)


**Note:** I didn't have a 3.3v relay on hand, and I really wanted to finish this project by the end of the night, so I just used a 5v relay and used a logic level shifter to conver the signal from the Spark Core to 5v. If you have a 3.3v relay you can just follow the instructions written. If you have a 5v relay, you'll need a level shifter, and a 5v source in addition to your 3v3. My level shifter has a 3.3v regulator on it, so I  powered my Spark Core with its output so that I wouldn't need two power supplies.

usage
-----

1. Open the Google Authenticator app.
2. Copy the 6 digit code.
3. Text the code to your Twilio phone number.
4. Your door should unlock.