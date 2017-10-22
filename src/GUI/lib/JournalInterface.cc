#include "JournalInterface.h"
#include <iostream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
JournalInterface* JournalInterface::journal_interface_ = NULL;
// -------------------------------------------------------------------------
JournalInterface::JournalInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml ) :
	journal_(NULL)
{
	if( !gladexml )
	{
		cerr << "JournalInterface(): Wrong glade!" << endl;
		throw;
	}
	gladexml->get_widget("journal1", journal_);
	if( !journal_ )
	{
		cerr << "JournalInterface(): No 'journal1' in glade!" << endl;
		throw;
	}
	Glib::signal_timeout().connect( sigc::mem_fun( this, &JournalInterface::poll ), getPollTimeout() );
}
// -------------------------------------------------------------------------
JournalInterface::~JournalInterface()
{
}
// -------------------------------------------------------------------------
JournalInterface*  JournalInterface::Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml )
{
	if( !journal_interface_ )
		journal_interface_ = new JournalInterface(gladexml);
	return journal_interface_;
}
// -------------------------------------------------------------------------
bool JournalInterface::poll()
{
	// не заканчиваем цикл вызова
	return true;
}
// -------------------------------------------------------------------------