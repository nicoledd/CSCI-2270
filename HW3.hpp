#pragma once
#include <iostream>

/* struct Country: node that will be stored in the CountryNetwork linked-list */
struct Country{
  /* name of the country */
  std::string name;
  /* message this country has received */
  std::string message;
  /* num of messages passed through this country */
  int numberMessages;
  /* pointer to the next country */
  Country* next;
};

/* class CountryNetwork: class for storing and manipulating Country linked-list */
class CountryNetwork{

  private:
    /* pointer to head of linked-list of countries */
    Country* head;

  public:
    /* default constructor */
    CountryNetwork();
    /* return true if network is empty, return false if network is not empty */
    bool isEmpty();
    /* insert a new country into network */
    void insertCountry(Country*, std::string);
    /* delete a country from network */
    void deleteCountry(std::string);
    /* load default country network */
    void loadDefaultSetup();
    /* search network for country, return pointer to found country */
    Country* searchNetwork(std::string);
    /* delete entire linked-list network */
    void deleteEntireNetwork();
    /* reverse the linked-list */
    void reverseEntireNetwork();
    /* return true if this is a valid input for 'prev country', else return false */
    bool validCountry(std::string);
    /* transmit message through network */
    void transmitMsg(std::string, std::string);
    /* print the linked-list network */
    void printPath();
};
