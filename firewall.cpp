#include "firewall.h"

bool Firewall::isPacketAlowed(const string& ipAddress )
{
	for (const auto& rule : firewallRules)
	{
		if (rule.ipAddress == ipAddress)
			return rule.allow;
	}
	return false;
}
void Firewall::addFirewallRule()
{
	string ipAddress;
	char choice;

	cout << "Enter IP Address: ";
	cin >> ipAddress;

	cout << "Allow or Block (a or b): ";
	cin >> choice;

	bool allow = (choice == 'a' || choice == 'A');
	firewallRules.push_back({ ipAddress,allow });

	cout << "Firewall rule added successfully. \n";
}
void Firewall::removeFirewallRule()
{
	string ipAddress;

	cout << "Enter IP address to remove: ";
	cin >> ipAddress;

	for (auto it = firewallRules.begin(); it != firewallRules.end(); ++it) {
		if (it->ipAddress == ipAddress) {
			firewallRules.erase(it);
			cout << "Firewall rule removed successfully." << endl;
			return;
		}
	}

	cout << "Firewall rule not found for the given IP address." << endl;
}
void Firewall::clearFirewallRules()
{
	firewallRules.clear();
	cout << "All firewall rules cleared." << endl;
}
void Firewall::printFirewallRules()
{
	cout << "Firewall Rules:" << endl;
	for (const auto& rule : firewallRules) {
		string action = rule.allow ? "Allow" : "Block";
		cout << "IP: " << rule.ipAddress << "  Action: " << action << endl;
	}
}
void Firewall::countFirewallRules()
{
	cout << "Total firewall rules: " << firewallRules.size() << endl;
}
void Firewall::searchFirewallRules()
{
	string ipAddress;

	cout << "Enter IP address to search: ";
	cin >> ipAddress;

	for (const auto& rule : firewallRules) {
		if (rule.ipAddress == ipAddress) {
			string action = rule.allow ? "Allow" : "Block";
			cout << "Firewall rule found for IP: " << rule.ipAddress << "  Action: " << action << endl;
			return;
		}
	}

	cout << "No firewall rule found for the given IP address." << endl;

}
void Firewall::blockAllTraffic()
{
	firewallRules.clear();
	firewallRules.push_back({ "0.0.0.0", false });
	cout << "All traffic blocked. Firewall rules updated." << endl;
}
void Firewall::allowAllTraffic()
{
	firewallRules.clear();
	firewallRules.push_back({ "0.0.0.0", true });
	cout << "All traffic allowed. Firewall rules updated." << endl;
}
void Firewall::blockAllTrafficFromRange()
{
	string startIp, endIp;

	cout << "Enter starting IP address: ";
	cin >> startIp;

	cout << "Enter ending IP address: ";
	cin >> endIp;

	firewallRules.push_back({ startIp, false });
	firewallRules.push_back({ endIp, false });

	cout << "Blocked traffic from IP range " << startIp << " to " << endIp << ". Firewall rules updated." << endl;

}
void Firewall::allowAllTrafficFromRange()
{
	string startIp, endIp;

	cout << "Enter starting IP address: ";
	cin >> startIp;

	cout << "Enter ending IP address: ";
	cin >> endIp;

	firewallRules.push_back({ startIp, true });
	firewallRules.push_back({ endIp, true });

	cout << "Allowed traffic from IP range " << startIp << " to " << endIp << ". Firewall rules updated." << endl;

}
void Firewall::blockAllTrafficbyProtocol()
{
	string protocol;

	cout << "Enter protocol to block: ";
	cin >> protocol;

	firewallRules.push_back({ protocol, false });

	cout << "Blocked traffic for protocol " << protocol << ". Firewall rules updated." << endl;

}
void Firewall::allowAllTrafficbyProtocol()
{
	string protocol;

	cout << "Enter protocol to allow: ";
	cin >> protocol;

	firewallRules.push_back({ protocol, true });

	cout << "Allowed traffic for protocol " << protocol << ". Firewall rules updated." << endl;

}
void Firewall::blockAllTrafficbyPort()
{
	string port;

	cout << "Enter port to block: ";
	cin >> port;

	firewallRules.push_back({ port, false });

	cout << "Blocked traffic for port " << port << ". Firewall rules updated." << endl;

}
void Firewall::allowAllTrafficbyPort()
{
	string port;

	cout << "Enter port to allow: ";
	cin >> port;

	firewallRules.push_back({ port, true });

	cout << "Allowed traffic for port " << port << ". Firewall rules updated." << endl;

}