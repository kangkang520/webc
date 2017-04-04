#include <iostream>
using namespace std;

#pragma comment (lib, "webc.lib")

#include <webc/webc.hpp>

using namespace webc::server;


int main() {
	
	querystring str = "name[]=222&#21457;&#30340;&#38463;&#20961;&#36798;&#21457;&#21457;&#36865;&#21040;&age=30";
	str.parse();

	string name = str.get<string>("age");

	cout << name << endl;

	//cout << str.get<string>("name") << endl;

	
	webc::server::httpserver *server = new webc::server::httpserver();

	if (server->create() == state::success) {
		cout << "ok" << endl;
		server->start();
	}

	system("pause");
	return 0;
}