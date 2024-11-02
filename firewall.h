#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;


class Firewall
{
private:
	struct FirewallRule
	{
		string ipAddress;
		bool allow;
	};
	vector<FirewallRule> firewallRules;
public:
	bool isPacketAlowed(const string& ipAddress);
	void addFirewallRule();
	void removeFirewallRule();
	void clearFirewallRules();
	void printFirewallRules();
	void countFirewallRules();
	void searchFirewallRules();
	void blockAllTraffic();
	void allowAllTraffic();
	void blockAllTrafficFromRange();
	void allowAllTrafficFromRange();
	void blockAllTrafficbyProtocol();
	void allowAllTrafficbyProtocol();
	void blockAllTrafficbyPort();
	void allowAllTrafficbyPort();

};

