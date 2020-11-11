/* simpleorganizer-window.c
 *
 * Copyright 2020 Nilanshu V Rajmane
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simpleorganizer-config.h"
#include "simpleorganizer-window.h"

struct _SimpleorganizerWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  //GtkHeaderBar        *header_bar;
  //GtkLabel            *label;
  HdySqueezer *squeezer;
  GtkBox *box;
  HdyHeaderBar *header_bar;
  HdyViewSwitcherBar *bottom_switcher;
  HdyViewSwitcher *headerbar_switcher;

};

static void
on_headerbar_squeezer_notify(HdySqueezer           *squeezer,
                             GdkEvent              *event,
                             SimpleorganizerWindow *self) {

  GtkWidget *child = hdy_squeezer_get_visible_child (squeezer);
  gboolean reveal = FALSE;

  if(child != (GtkWidget *)self->headerbar_switcher) {
    reveal = TRUE;
  }

  if(HDY_IS_VIEW_SWITCHER_BAR (self->bottom_switcher)){
    hdy_view_switcher_bar_set_reveal (self->bottom_switcher, reveal);
  }
}

G_DEFINE_TYPE (SimpleorganizerWindow, simpleorganizer_window, GTK_TYPE_APPLICATION_WINDOW)

static void
simpleorganizer_window_class_init (SimpleorganizerWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  //object_class->constructed = simpleorganizer_window_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/io/github/nilanshu96/SimpleOrganizer/simpleorganizer-window.ui");
  gtk_widget_class_bind_template_child (widget_class, SimpleorganizerWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, SimpleorganizerWindow, squeezer);
  gtk_widget_class_bind_template_child (widget_class, SimpleorganizerWindow, bottom_switcher);
  gtk_widget_class_bind_template_child (widget_class, SimpleorganizerWindow, headerbar_switcher);
  gtk_widget_class_bind_template_child (widget_class, SimpleorganizerWindow, box);
 // gtk_widget_class_bind_template_child (widget_class, SimpleorganizerWindow, label);
}

static void
on_destroy (SimpleorganizerWindow *app) {
  /* added to avoid the following errors
   * hdy_view_switcher_get_stack: assertion 'HDY_IS_VIEW_SWITCHER (self)' failed
   * hdy_view_switcher_get_stack: assertion 'HDY_IS_VIEW_SWITCHER (self)' failed
   * no idea why this is occuring
   */
  gtk_widget_destroy (app->headerbar_switcher);
}

static void
simpleorganizer_window_init (SimpleorganizerWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  if(HDY_IS_SQUEEZER (self->squeezer)) {
    g_signal_connect (self->squeezer, "notify::visible-child", G_CALLBACK (on_headerbar_squeezer_notify), self);
  }
  g_signal_connect (self, "destroy", G_CALLBACK (on_destroy), NULL);
}
