/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * Pan - A Newsreader for Gtk+
 * Copyright (C) 2002-2006  Charles Kerr <charles@rebelbase.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __Progress_View_h__
#define __Progress_View_h__

#include "gtk-compat.h"
#include <pan/general/progress.h>

namespace pan
{
  /**
   * GtkProgressBar representations of general::Progress objects.
   *
   * These are used at the bottom of Pan's main window to show
   * the status of running Task objects.
   *
   * @ingroup GUI
   */
  class ProgressView:
    private Progress::Listener
  {
    public:
      ProgressView ();
      virtual ~ProgressView () { set_progress(0); }
      GtkWidget* root () { return _root; }
      void set_progress (Progress *);
      Progress* get_progress () { return _progress; }
      const Progress* get_progress () const { return _progress; }

    private: // inherited from progress listener
      virtual void on_progress_step (Progress&, int percentage);
      virtual void on_progress_status (Progress&, const StringView&);
      virtual void on_progress_error (Progress&, const StringView&);
      virtual void on_progress_finished (Progress&, int) { }

    private:
      void update_text_soon ();
      void update_percentage_soon ();
      guint _progress_step_idle_tag;
      guint _progress_status_idle_tag;
      static gboolean on_progress_step_idle (gpointer);
      static gboolean on_progress_status_idle (gpointer);

    private:
      GtkWidget * _root;
      GtkWidget * _progressbar;
      std::string _last_status;
      Progress * _progress;
  };
}

#endif
