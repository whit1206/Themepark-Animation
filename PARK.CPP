#include "park.h"
#include "parkgates.h"
#include "eventscheduler.h"
#include "walkway.h"
#include "connector.h"
#include "smartConnector.h"
#include "ferriswheel.h"

#include "boxes.h"
//#include "ticketoffice.h"
//#include "bathroom.h"
//#include "hotdogstand.h"
#include "centrifuge.h"
#include "gondola.h"
#include "rollercoaster.h"
#include "globals.h"

#include <stdlib.h>

int viewdegree = 0;
double global_y_ratio = 1;
int viewangle = 25;
double zoom_factor = 1;

Park::Park() {
	parkSize = 0;
	viewdegree = 0;
	viewangle = 25;
	global_y_ratio = 1 / sin((viewangle+.0001) * PI / 180);
	zoom_factor = 1;
	GP142_show_text(0);
	display.setAnimation(Run);
	
	scheduler = new EventScheduler(this);

	build();
}


Park::~Park() {
	for (int i=0; i<parkSize; i++)
		delete parkElements[i];
}


void Park::open() {
	gates->open();	
}


void Park::pause(int ticks) {

	// this should call pause() to avoid eating 100% of CPU time but then the picture is
	// not very nice

	for (int i=0; i<ticks; i++) {
		// we can't just pause(); that would make the window constantly busy
		// dummy vars
		int mouseX, mouseY;
		char keyPressed;

		// not the best place to handle quits
		GP142Event event = display.getNextEvent(mouseX, mouseY, keyPressed);
		if (event == Quit)
			exit(0);
		else if (event == Mouse)
		{
			if(mouseY > 219 && mouseY < 241)
			{
				if(mouseX > 119 && mouseX < 141) //+ button
					viewdegree = (viewdegree + 350) % 360;
				if(mouseX > 199 && mouseX < 221) //- button
					viewdegree = (viewdegree + 10) % 360;
			}
			if(mouseY > 189 && mouseY < 211)
			{
				if(mouseX > 119 && mouseX < 141 && viewangle > 0) //+ button
					viewangle -= 5;
				if(mouseX > 199 && mouseX < 221 && viewangle < 90) //- button
					viewangle += 5;
				if(mouseX > -221 && mouseX < -199 && zoom_factor > .55) //+ button
					zoom_factor -= .1;
				if(mouseX > -141 && mouseX < -119 && zoom_factor < 2) //- button
					zoom_factor += .1;
				global_y_ratio = 1 / sin((viewangle+.0001) * PI / 180);
			}

		}
		else if (event == Key)
		{
			if (keyPressed == '8' && viewangle < 90)
				viewangle += 5;
			if (keyPressed == '2' && viewangle > 0)
				viewangle-= 5;
			if (keyPressed == '4')
				viewdegree = (viewdegree + 350) % 360;
			if (keyPressed == '6')
				viewdegree = (viewdegree + 10) % 360;
			if (keyPressed == '+' && zoom_factor < 2)
				zoom_factor += .1;
			if (keyPressed == '-' && zoom_factor > 0.55)
				zoom_factor -= .1;
			if (keyPressed == '5')
			{
				viewdegree = 0;
				viewangle = 25;
				zoom_factor = 1;
			}
			global_y_ratio = 1 / sin((viewangle+.0001) * PI / 180);
		}
	}
	
}


void Park::repaint() {
	display.clear(White);
	display.write(-100, 190, "Six Flags UW", Magenta, 36);
	display.write(-280, 230, "Adam Fuchs #9931263", MedGray, 12);
	display.write(-280, 215, "Chris Whitten #9928188", MedGray, 12);
//	display.drawLine(0,-200,0,200,Black,1);
//	display.drawLine(-10,0,10,0,Black,1);
	
	//buttons to rotate image
	display.drawRectangle(120,220,140,240,Black,2);
	display.drawRectangle(200,220,220,240,Black,2);
	display.write(125, 219, "-", Black,20);
	display.write(205, 219, "+", Black,20);

	display.drawRectangle(120,210,140,190,Black,2);
	display.drawRectangle(200,210,220,190,Black,2);
	display.write(125, 189, "-", Black,20);
	display.write(205, 189, "+", Black,20);

	//buttons to zoom
	display.drawRectangle(-120,210,-140,190,Black,2);
	display.drawRectangle(-200,210,-220,190,Black,2);
	display.write(-135, 189, "+", Black,20);
	display.write(-215, 189, "-", Black,20);


	//draw viewdegree text
	char c[10];
	itoa(viewdegree,c,10);
	strcat(c,"°");
	display.write(155, 219, c, Blue,20);

	//draw viewangle text
	itoa(viewangle,c,10);
	strcat(c,"°");
	display.write(155, 189, c, Blue,20);

	//draw zoom_factor text
	itoa((int)(zoom_factor * 10 + 10),c,10);
	char d[11];
	d[0] = (char)((int)c[0]-1);
	d[1] = '.';
	d[2] = c[1];
	display.write(-185, 189, d, Blue,20);

	int i;
	for (i=1; i<parkSize; i++) {
		parkElements[i]->setXY();
	}

	for (i=0; i<parkSize; i++) {
		parkElements[i]->paint(display);
	}
}


void Park::build() {
	gates = new ParkGates();
	addElement(gates);
	gates->connectTo(gates);

	//QBox for all attractions
	QBox* qb;

//*****attractions****************
	//*****gondolas*****
	//gondola and queue box
	qb = new QBox(250, 0, 90, 270, 30);
	Gondola* gda = new Gondola(250, 0, 90, qb);
	addElement(gda);
	//gondola and queue box compliments
	qb = new QBox(250, 0, 270, 270, 30);
	Gondola* gdb = new Gondola(250, 0, 270, qb);
	addElement(gdb);

	//*****rollercoaster*****
	qb = new QBox(230, 50, 333, 290, 30);
	Rollercoaster* rc = new Rollercoaster(290,0,335,25,qb);
	addElement(rc);

	//*****centrifuge*****
	qb = new QBox(230, 0, 135, 270, 30);
	Centrifuge* cf = new Centrifuge(280, 0, 135, 0, qb);
	addElement(cf);

	//*****ferris wheel*****
	qb = new QBox(230, 0, 180, 270, 30);
	FerrisWheel* fw = new FerrisWheel(230, 0, 180, 90, qb);
	addElement(fw);

	//*****bathrooms*****
	//women's room and queue box
	qb = new QBox(30, 0, 0, 90, 36);
	Bathroom* brW = new Bathroom(20, 0, 0, 0, 1, qb);
	addElement(brW);

	//men's room and queue box
	qb = new QBox(30, 0, 180, 90, 36);
	Bathroom* brM = new Bathroom(20, 0, 180, 180, 0, qb);
	addElement(brM);

	//*****ticket office*****
	qb = new QBox(240, 0, 225, 90, 40);
	TicketOffice* TO = new TicketOffice(220, 0, 225, 45, qb);
	addElement(TO);

	//*****hot dog stand?*****
	qb = new QBox(230, 0, 30, 270, 30);
	HotDogStand* hd = new HotDogStand(250, 0, 30, 30, qb);
	addElement(hd);

	
//*****walkways*******************
/**/	//gates to TO
	WalkWay* wwgate_TO = new WalkWay(300, 0, 225, 280, 0, 225);
	addElement(wwgate_TO);
	gates->connectTo(wwgate_TO);
	wwgate_TO->connectTo(TO);

	//TO to exit
	WalkWay* wwTO_ex = new WalkWay(200, 0, 225, 200, 0, 232);
	addElement(wwTO_ex);
	WalkWay* wwTO_ex1 = new WalkWay(200, 0, 232, 260, 0, 230);
	addElement(wwTO_ex1);
	WalkWay* wwTO_ex2 = new WalkWay(260, 0, 230, 300, 0, 225);
	addElement(wwTO_ex2);
	wwTO_ex->connectTo(wwTO_ex1);
	wwTO_ex1->connectTo(wwTO_ex2);
	wwTO_ex2->connectTo(gates);
	TO->connectTo(wwTO_ex);

	//TO to gdb
	WalkWay* wwTO_gdb = new WalkWay(200, 0, 225, 200, 0, 270);
	addElement(wwTO_gdb);
	WalkWay* wwgdb_TO = new WalkWay(200, 0, 270, 200, 0, 225);
	addElement(wwgdb_TO);
	//TO to sc1
	WalkWay* wwTO_sc1 = new WalkWay(200, 0, 225, 75, 0, 270);
	addElement(wwTO_sc1);
	WalkWay* wwsc1_TO = new WalkWay(75, 0, 270, 200, 0, 225);
	addElement(wwsc1_TO);
	//TO fo fw
	WalkWay* wwTO_fw = new WalkWay(200, 0, 225, 200, 0, 180);
	addElement(wwTO_fw);
	WalkWay* wwfw_TO = new WalkWay(200, 0, 180, 200, 0, 225);
	addElement(wwfw_TO);
	//gdb to sc1
	WalkWay* wwgdb_sc1 = new WalkWay(200, 0, 270, 75, 0, 270);
	addElement(wwgdb_sc1);
	WalkWay* wwsc1_gdb = new WalkWay(75, 0, 270, 200, 0, 270);
	addElement(wwsc1_gdb);
	//gdb to rc
	WalkWay* wwgdb_rc = new WalkWay(200, 0, 270, 200, 50, 330);
	addElement(wwgdb_rc);
	WalkWay* wwrc_gdb = new WalkWay(200, 50, 330, 200, 0, 270);
	addElement(wwrc_gdb);
	//gdb to fw
	WalkWay* wwgdb_fw = new WalkWay(200, 0, 270, 200, 0, 180);
	addElement(wwgdb_fw);
	WalkWay* wwfw_gdb = new WalkWay(200, 0, 180, 200, 0, 270);
	addElement(wwfw_gdb);
	//fw to cf
	WalkWay* wwfw_cf = new WalkWay(200, 0, 180, 200, 0, 135);
	addElement(wwfw_cf);
	WalkWay* wwcf_fw = new WalkWay(200, 0, 135, 200, 0, 180);
	addElement(wwcf_fw);
	//fw to gda
	WalkWay* wwfw_gda = new WalkWay(200, 0, 180, 200, 0, 90);
	addElement(wwfw_gda);
	WalkWay* wwgda_fw = new WalkWay(200, 0, 90, 200, 0, 180);
	addElement(wwgda_fw);
	//cf to sc2
	WalkWay* wwcf_sc2 = new WalkWay(200, 0, 135, 75, 0, 90);
	addElement(wwcf_sc2);
	WalkWay* wwsc2_cf = new WalkWay(75, 0, 90, 200, 0, 135);
	addElement(wwsc2_cf);
	//cf to gda
	WalkWay* wwcf_gda = new WalkWay(200, 0, 135, 200, 0, 90);
	addElement(wwcf_gda);
	WalkWay* wwgda_cf = new WalkWay(200, 0, 90, 200, 0, 135);
	addElement(wwgda_cf);
	//gda to sc2
	WalkWay* wwgda_sc2 = new WalkWay(200, 0, 90, 75, 0, 90);
	addElement(wwgda_sc2);
	WalkWay* wwsc2_gda = new WalkWay(75, 0, 90, 200, 0, 90);
	addElement(wwsc2_gda);
	//gda to hd
	WalkWay* wwgda_hd = new WalkWay(200, 0, 90, 200, 0, 30);
	addElement(wwgda_hd);
	WalkWay* wwhd_gda = new WalkWay(200, 0, 30, 200, 0, 90);
	addElement(wwhd_gda);
	//hd to sc2
	WalkWay* wwhd_sc2 = new WalkWay(200, 0, 30, 75, 0, 90);
	addElement(wwhd_sc2);
	WalkWay* wwsc2_hd = new WalkWay(75, 0, 90, 200, 0, 30);
	addElement(wwsc2_hd);
	//hd to rc
	WalkWay* wwhd_rc = new WalkWay(200, 0, 30, 200, 50, 330);
	addElement(wwhd_rc);
	WalkWay* wwrc_hd = new WalkWay(200, 50, 330, 200, 0, 30);
	addElement(wwrc_hd);
	//rc to sc1
	WalkWay* wwrc_sc1 = new WalkWay(200, 50, 330, 75, 0, 270);
	addElement(wwrc_sc1);
	WalkWay* wwsc1_rc = new WalkWay(75, 0, 270, 200, 50, 330);
	addElement(wwsc1_rc);
	//sc1 to br
	WalkWay* wwsc1_brW = new WalkWay(75, 0, 270, 75, 0, 330);
	addElement(wwsc1_brW);
	WalkWay* wwsc1_brW1 = new WalkWay(75, 0, 330, 65, 0, 0);
	addElement(wwsc1_brW1);
	wwsc1_brW->connectTo(wwsc1_brW1);
	wwsc1_brW1->connectTo(brW);
	WalkWay* wwsc1_brM = new WalkWay(75, 0, 270, 75, 0, 210);
	addElement(wwsc1_brM);
	WalkWay* wwsc1_brM1 = new WalkWay(75, 0, 210, 65, 0, 180);
	addElement(wwsc1_brM1);
	wwsc1_brM->connectTo(wwsc1_brM1);
	wwsc1_brM1->connectTo(brM);
	//sc2 to br
	WalkWay* wwsc2_brW = new WalkWay(75, 0, 90, 75, 0, 30);
	addElement(wwsc2_brW);
	WalkWay* wwsc2_brW1 = new WalkWay(75, 0, 30, 65, 0, 0);
	addElement(wwsc2_brW1);
	wwsc2_brW->connectTo(wwsc2_brW1);
	wwsc2_brW1->connectTo(brW);
	WalkWay* wwsc2_brM = new WalkWay(75, 0, 90, 75, 0, 150);
	addElement(wwsc2_brM);
	WalkWay* wwsc2_brM1 = new WalkWay(75, 0, 150, 65, 0, 180);
	addElement(wwsc2_brM1);
	wwsc2_brM->connectTo(wwsc2_brM1);
	wwsc2_brM1->connectTo(brM);
	//br to sc1
	WalkWay* wwbr_sc1 = new WalkWay(0, 0, 0, 75, 0, 270);
	addElement(wwbr_sc1);
	//br to sc2
	WalkWay* wwbr_sc2 = new WalkWay(0, 0, 0, 75, 0, 90);
	addElement(wwbr_sc2);

//*****switches*******************
	//switch A
	Connector* ca1 = new Connector(wwTO_gdb,wwTO_fw);
	addElement(ca1);
	Connector* ca2 = new Connector(wwTO_gdb,wwTO_sc1);
	addElement(ca2);
	Connector* ca3 = new Connector(wwTO_fw,wwTO_sc1);
	addElement(ca3);
	Connector* ca4 = new Connector(wwTO_ex,ca1,.3);
	addElement(ca4);
	Connector* ca5 = new Connector(wwTO_ex,ca2,.3);
	addElement(ca5);
	Connector* ca6 = new Connector(wwTO_ex,ca3,.3);
	addElement(ca6);
	TO->connectTo(ca1);
	wwsc1_TO->connectTo(ca4);
	wwfw_TO->connectTo(ca5);
	wwgdb_TO->connectTo(ca6);

	//switch B
	Connector* cb1 = new Connector(wwfw_TO,wwfw_gda);
	addElement(cb1);
	Connector* cb2 = new Connector(wwfw_gdb,wwfw_cf);
	addElement(cb2);
	Connector* cb3 = new Connector(cb1,cb2);
	addElement(cb3);
	Connector* cb4 = new Connector(fw,cb3);
	addElement(cb4);
	fw->connectTo(cb3);
	wwTO_fw->connectTo(cb4);
	wwgda_fw->connectTo(cb4);
	wwgdb_fw->connectTo(cb4);
	wwcf_fw->connectTo(cb4);


	//switch C
	Connector* cc1 = new Connector(wwcf_gda,wwcf_fw);
	addElement(cc1);
	Connector* cc2 = new Connector(wwcf_gda,wwcf_sc2);
	addElement(cc2);
	Connector* cc3 = new Connector(wwcf_fw,wwcf_sc2);
	addElement(cc3);
	Connector* cc4 = new Connector(cf,cc1);
	addElement(cc4);
	Connector* cc5 = new Connector(cf,cc2);
	addElement(cc5);
	Connector* cc6 = new Connector(cf,cc3);
	addElement(cc6);
	cf->connectTo(cc1);
	wwsc2_cf->connectTo(cc4);
	wwfw_cf->connectTo(cc5);
	wwgda_cf->connectTo(cc6);

	//switch D
	Connector* cd1 = new Connector(wwgda_fw,wwgda_cf);
	addElement(cd1);
	Connector* cd2 = new Connector(wwgda_sc2,wwgda_hd);
	addElement(cd2);
	Connector* cd3 = new Connector(cd1,cd2);
	addElement(cd3);
	Connector* cd4 = new Connector(gda,cd3,.2);
	addElement(cd4);
	gdb->connectTo(cd3);
	wwcf_gda->connectTo(cd4);
	wwhd_gda->connectTo(cd4);
	wwsc2_gda->connectTo(cd4);
	wwfw_gda->connectTo(cd4);


	//switch E
	Connector* ce1 = new Connector(wwhd_gda,wwhd_rc);
	addElement(ce1);
	Connector* ce2 = new Connector(wwhd_gda,wwhd_sc2);
	addElement(ce2);
	Connector* ce3 = new Connector(wwhd_rc,wwhd_sc2);
	addElement(ce3);
	Connector* ce4 = new Connector(hd,ce1);
	addElement(ce4);
	Connector* ce5 = new Connector(hd,ce2);
	addElement(ce5);
	Connector* ce6 = new Connector(hd,ce3);
	addElement(ce6);
	hd->connectTo(ce1);
	wwsc2_hd->connectTo(ce4);
	wwrc_hd->connectTo(ce5);
	wwgda_hd->connectTo(ce6);

	//switch F
	Connector* cf1 = new Connector(wwrc_gdb,wwrc_hd);
	addElement(cf1);
	Connector* cf2 = new Connector(wwrc_gdb,wwrc_sc1);
	addElement(cf2);
	Connector* cf3 = new Connector(wwrc_hd,wwrc_sc1);
	addElement(cf3);
	Connector* cf4 = new Connector(rc,cf1);
	addElement(cf4);
	Connector* cf5 = new Connector(rc,cf2);
	addElement(cf5);
	Connector* cf6 = new Connector(rc,cf3);
	addElement(cf6);
	rc->connectTo(cf4);
	wwsc1_rc->connectTo(cf4);
	wwhd_rc->connectTo(cf5);
	wwgdb_rc->connectTo(cf6);

	//switch G
	Connector* cg1 = new Connector(wwgdb_fw,wwgdb_TO);
	addElement(cg1);
	Connector* cg2 = new Connector(wwgdb_sc1,wwgdb_rc);
	addElement(cg2);
	Connector* cg3 = new Connector(cg1,cg2);
	addElement(cg3);
	Connector* cg4 = new Connector(gdb,cg3,.2);
	addElement(cg4);
	gda->connectTo(cg3);
	wwTO_gdb->connectTo(cg4);
	wwrc_gdb->connectTo(cg4);
	wwsc1_gdb->connectTo(cg4);
	wwfw_gdb->connectTo(cg4);

	//switch H
	SmartConnector* ch1 = new SmartConnector(wwsc1_brW,wwsc1_brM);
	addElement(ch1);
	Connector* ch2 = new Connector(wwsc1_rc,wwsc1_TO);
	addElement(ch2);
	Connector* ch3 = new Connector(wwsc1_gdb,ch2);
	addElement(ch3);
	wwbr_sc1->connectTo(ch3);
	wwgdb_sc1->connectTo(ch1);
	wwrc_sc1->connectTo(ch1);
	wwTO_sc1->connectTo(ch1);

	//switch I
	SmartConnector* ci1 = new SmartConnector(wwsc2_brW,wwsc2_brM);
	addElement(ci1);
	Connector* ci2 = new Connector(wwsc2_hd,wwsc2_cf);
	addElement(ci2);
	Connector* ci3 = new Connector(wwsc2_gda,ci2);
	addElement(ci3);
	wwbr_sc2->connectTo(ci3);
	wwgda_sc2->connectTo(ci1);
	wwhd_sc2->connectTo(ci1);
	wwcf_sc2->connectTo(ci1);

	//switch J
	Connector* cj1 = new Connector(wwbr_sc1,wwbr_sc2);
	addElement(cj1);
	brW->connectTo(cj1);
	brM->connectTo(cj1);


}


void Park::addElement(ParkElement* pe) {
	parkElements[parkSize++] = pe;
}
