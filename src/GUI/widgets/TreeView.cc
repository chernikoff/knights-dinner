#include <iostream>
#include <gdkmm.h>
#include <math.h>
#include <librsvg/rsvg.h>
#include "TreeView.h"
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_ROUNDTABLE_PROPERTIES() \
	tree_model_ref_(Glib::RefPtr<Gtk::ListStore>()) \
	,row_number_(0)
// -------------------------------------------------------------------------
void TreeView::constructor()
{
	cout << "TreeView::constructor()" << endl;
	
	columns_ = &tree_model_columns_;
	add(tree_view_);
	//set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	tree_view_.show();
}
// -------------------------------------------------------------------------
TreeView::TreeView() :
	Glib::ObjectBase("treeview")
	,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
TreeView::TreeView( Gtk::ScrolledWindow::BaseObjectType* gobject ) :
	Gtk::ScrolledWindow(gobject)
	,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
TreeView::~TreeView()
{
}
//-----------------------------------------------------------------------------------------------------
void TreeView::on_realize()
{
	init_treeview();
	Gtk::ScrolledWindow::on_realize();
}
//-----------------------------------------------------------------------------------------------------
Gtk::TreeViewColumn* TreeView::add_column(const std::string& name, Gtk::CellRenderer* renderer)
{
	tree_view_.append_column(name, *renderer);
	int pos = columns_map.size();
	columns_map[name].column = tree_view_.get_column(pos);
	columns_map[name].pos = pos;
	return columns_map[name].column;
}
// -------------------------------------------------------------------------
void TreeView::init_treeview()
{
	if( tree_model_ref_ )
		return;
	
	tree_model_ref_ = Gtk::ListStore::create(*columns_);
	tree_view_.set_model(tree_model_ref_);
	tree_view_.get_selection()->set_mode(Gtk::SELECTION_NONE);

	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("№", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(number));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(32);
		pRenderer->property_xalign() = 0.5;
	}
}
// -------------------------------------------------------------------------
unsigned int TreeView::addRow()
{
	Gtk::TreeIter iter = tree_model_ref_->append();
	Gtk::TreeRow row = *iter;
	row[COLUMN(number)] = ++row_number_;
	row[COLUMN(time)] = time(NULL);
	// перемещаемся но добавленную строку
	Gtk::TreePath path(row);
	tree_view_.scroll_to_row(path);
	return row_number_;
}
// -------------------------------------------------------------------------
void TreeView::clear()
{
	tree_model_ref_->clear();
	row_number_ = 0;
}
// -------------------------------------------------------------------------
