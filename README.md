# FlightSimulator Exercise Project:  
1. [Introduction](#introduction)  
2. [Our Project:](#our-project)  
3. [Dependencies:](#dependencies)  
4. [Installation:](#installation)


## Introduction
As part of an advanced programming course we were given a task to teach us different elements:
* Use of design and architecture templates.
* Communications and server-client architecture.
* Using data structures and database.
* Streaming data (files and communications)
* Comparison, selection and assimilation of algorithms within the system we create.
* Parallel programming using treads.
* Event-oriented programming, a desktop application with a GUI.
* Mobile application (Android).

## Our Project:
In this project we will write an interpreter to a UAV control code (Unmanned aerial vehicle).
Our plane will fly in cyberspace FlightGear Flight Simulator. This simulator is also a server that you can connect to as a client (and vice versa), so we can easily pull out Information about the various parameters of the flight in real time and even injecting orders for him to drive the plane.

## Dependencies:
* MacOS / Linux
* FlightGear 2018.3.1
* Git

## Installation:
1. Clone the repository:  
    ```
    $ git clone https://github.com/eyalcohen308/FlightSimulator.git
    ```
2. download flight simulator:
    ```
    $ sudo add-apt-repository ppa:saiarcot895/flightgear
    $ sudo apt-get update
    ```
3. Enter the project's directory:
    ```
    $ cd FlightSimulator
    ```
