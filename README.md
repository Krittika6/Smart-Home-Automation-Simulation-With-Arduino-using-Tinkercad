# Smart-Home-Automation-Simulation-With-Arduino-using-Tinkercad
Mini Home Automation Dashboard (Arduino + Tinkercad)

A simulated home automation system built using Arduino (Embedded C++) and Tinkercad, featuring:

-Password-protected access

-Real-time appliance control

-Device status monitoring

-Non-blocking scheduling (using millis())

**This project requires no physical hardware and runs entirely in Tinkercad.

Features
- Password Login:

Commands are locked until user logs in after typing:

LOGIN 1234

-Control Appliances (A, B, C, D)

Example:

ON A
OFF C

-Status Command

Shows ON/OFF status of all devices:

STATUS

-Scheduling System

Schedule future ON/OFF actions:

SCHEDULE B ON AFTER 5
SCHEDULE D OFF AFTER 12


Up to 4 scheduled tasks (one for each device)

Uses millis() → non-blocking real-time scheduling

Circuit (Tinkercad)
Device	Arduino Pin	Component
A	2	LED + 220Ω (RED)
B	3	LED + 220Ω (GREEN)
C	4	LED + 220Ω (YELLOW)
D	5	LED + 220Ω (BLUE)

All LED cathodes → GND.
No additional components required.

 Run Instructions

Open project in Tinkercad

Upload .ino code

Start simulation

Open Serial Monitor

Baud: 9600

Line ending: Newline

Login:

LOGIN 1234


Start controlling devices or scheduling tasks.

Technologies Used

-Embedded C++ (Arduino)

-Microcontroller programming (ATmega328P)

-UART serial communication

-Finite State Machine (login state)

-Real-time scheduling using millis()

-Event-driven programming

DEMO PIC:
<img width="1335" height="914" alt="image" src="https://github.com/user-attachments/assets/9b51532c-4884-426f-94d9-366a0b83674d" />

PROJECT LINK:  https://www.tinkercad.com/things/hfXVIbCOCai/editel?returnTo=%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=tLdcVEmvu9flJRCGAtAfOJmoxGG-JNU-ArdKU69JbNQ
