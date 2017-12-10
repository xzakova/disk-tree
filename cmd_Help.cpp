#include "headers.h"
#include "cmd_Handlers.h"

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace cmd;
using namespace tree;

Handler cmd::Help(const Options & options)
{
	return[command = options.path](Node * node, std::ostream & out)
	{
		if (command == "/") {
			out<<"Dostupne prikazy: quit, list, size, tree, dump, rm, mkdir, link, touch ";
		}
		else if (command == "quit") {
			out<< "ukoncenie prace s aplikaciou";
		}
		else if (command == "list") {
			out<<"vypis definovaneho adresara (path) alebo hlavneho adresara (default), s moznostou 'sledovat' linky (follow) alebo sa rekurzivne vnarat do adresarov (recursive)";
		}
		else if (command == "size") {
			out<< "vypis velkosti suboru/adresara, je mozne zahrnut odkazovane subory/adresare (follow) alebo rekurzivne pridat vnorene adresare (recursive)";
		}
		else if (command == "tree") {
			out<<"zobrazenie stromovej struktury pre danu cestu (path) alebo pre hlavny adresar (default); zobrazenie podobne ako prikaz tree pre MS Windows";
		}
		else if (command == "dump") {
			out<<"vypis hierarchie danej cesty (default - hlavny adresar) v json formate";
		}
		else if (command == "rm") {
			out<< "zmazanie suboru/adresara/odkazu";
		}
		else if (command == "mkdir") {
			out<< "vytvorenie adresara";
		}
		else if (command == "link") {
			out<< "vytvorenie odkazu";
		}
		else if (command == "touch") {
			out<<"vytvorenie suboru (default velkost je 0B)";
		}
		else {
			out << "Prikaz neexistuje";
		}

		return true;
	};

}