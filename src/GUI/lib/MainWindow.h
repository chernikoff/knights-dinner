#ifndef _MainWindow_H_
#define _MainWindow_H_
// ------------------------------------------------------------------------------
#include <gtkmm.h>
#include "Dinner/Dinner.h"
// ------------------------------------------------------------------------------
namespace knights
{
	class MainWindow;
	extern MainWindow* gwindow;

	class MainWindow
	{
		public:
			static MainWindow* Instance(std::string gladedir, std::string guifile, std::string svgdir);
			Gtk::Window* w;
			
		protected:
			MainWindow(std::string gladedir, std::string guifile, std::string svgdir);
			MainWindow();
			~MainWindow();
			virtual void on_show();
			static bool on_start(GtkWidget* w);
			static bool on_continue(GtkWidget* w);
			static bool on_stop(GtkWidget* w);
			static bool on_choose(GtkWidget* w);

		private:
			void draw_splash(const double& perc);
			Dinner* make_dinner(const Dinner* copy = NULL);

			double progress;
			Gtk::Window splash;
			Gtk::Alignment alignment;
			Gtk::ProgressBar bar;
			Dinner* dinner;
			enum Algorithm
			{
				SIMPLE_ALGORITHM,
				HUNGRY_ALGORITHM,
				PRIPORITY_ALGORITHM,
				SMART_ALGORITHM
			};
			Algorithm algorithm;
	};
}
// ------------------------------------------------------------------------------
#endif // _MainWindow_H_
// ------------------------------------------------------------------------------
