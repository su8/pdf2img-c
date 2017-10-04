/*
   Copyright 06/10/2017
 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include <sys/stat.h>
#include <gtk/gtk.h>
#include <locale.h>
#include "gettext.h"
#include "my_constants.h"

/* string comparison */
#define STREQ(x, z) (0 == strcmp(x, z))

/* function prototypes */
void on_image_combo(void);
void on_sdevice_combo(void);
void on_about_clicked(void);
void on_button1_clicked(void);
void on_button2_clicked(void);
void pdf_to_img(const char *filename);
void RaiseWarning(const char *str_to_warn1, const char *str_to_warn2);
size_t index_last_sep(const char *str);

/* gtk related classes */
GtkWidget *window, *spinbutton1, *spinbutton2, *about_label, *sdev_combo;
GtkWidget *entry, *alias_combo, *trans_switch, *image_combo;
char last_pdf[VLA+1];

int main(int argc, char *argv[]) {

  /* Localization */
  if (!setlocale(LC_ALL, "")) {
    return EXIT_FAILURE;
  }
  textdomain(GETTEXT_PACKAGE);
  bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

  GtkWidget *from_label, *to_label, *button1_lbl, *about_button, *expand1;
  GtkWidget *image_label, *sdevice_lbl, *expand2, *grid, *entry_label;
  GtkWidget *button1, *button2, *button2_lbl;

  gtk_init(&argc, &argv);

  window       = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), _(PROGRAM_TITLE));
  gtk_container_set_border_width(GTK_CONTAINER(window), 6);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 20);
  gtk_window_set_default_icon_from_file(PROGRAM_ICON, NULL);

  if (DECORATE_VIA_CUSTOM_CSS)  {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, APP_CSS, -1, NULL);
    /* GtkStyleContext *context = gtk_widget_get_style_context(window); */
    GdkScreen *screen = gtk_widget_get_screen(GTK_WIDGET(window));
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
  }

  grid         = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 7);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
  gtk_container_set_border_width(GTK_CONTAINER(grid), 2);
  gtk_container_add(GTK_CONTAINER(window), grid);

  entry_label  = gtk_label_new(_(RESOLUTION_LBL));
  gtk_grid_attach(GTK_GRID(grid), entry_label, POSITION_LEFT, 1, 1, 1);

  /* entry        = gtk_entry_new(); */
  /* gtk_entry_set_width_chars(GTK_ENTRY(entry), 1); */
  /* gtk_entry_set_text(GTK_ENTRY(entry), RESOLUTION_NUM); */
  /* gtk_entry_set_max_length(GTK_ENTRY(entry), 4); */
  entry        = gtk_spin_button_new_with_range(100, 9999, 1);
  gtk_grid_attach(GTK_GRID(grid), entry, POSITION_LEFT, 2, 1, 1);

  if (SHOW_IMAGES_ON_BUTTONS) {
    /* gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "video-display"); */
    about_label  = gtk_label_new(_(ABOUT_LBL)); 
    gtk_grid_attach(GTK_GRID(grid), about_label, POSITION_RIGHT, 1, 1, 1);
    about_button = gtk_button_new_from_icon_name("starred", GTK_ICON_SIZE_BUTTON);
    button1      = gtk_button_new_from_icon_name("folder-documents", GTK_ICON_SIZE_BUTTON);
  } else {
    about_button = gtk_button_new_with_label(_(ABOUT_LBL));
    button1      = gtk_button_new_with_label(_(BUTTONE_LBL));
  }
  
  g_signal_connect(G_OBJECT(about_button), "clicked", G_CALLBACK(on_about_clicked), NULL);
  gtk_grid_attach(GTK_GRID(grid), about_button, POSITION_RIGHT, 2, 1, 1);

  from_label   = gtk_label_new(_(FROM_LBL));
  gtk_grid_attach(GTK_GRID(grid), from_label, POSITION_LEFT, 4, 1, 1);

  spinbutton1  = gtk_spin_button_new_with_range(1, 9999, 1);
  gtk_grid_attach(GTK_GRID(grid), spinbutton1, POSITION_LEFT, 5, 1, 1);

  to_label     = gtk_label_new(_(TO_LBL));
  gtk_grid_attach(GTK_GRID(grid), to_label, POSITION_RIGHT, 4, 1, 1);

  spinbutton2  = gtk_spin_button_new_with_range(1, 9999, 1);
  gtk_grid_attach(GTK_GRID(grid), spinbutton2, POSITION_RIGHT, 5, 1, 1);

  image_label  = gtk_label_new(_(IMG_LBL));
  gtk_grid_attach(GTK_GRID(grid), image_label, POSITION_LEFT, 6, 1, 1);

  unsigned short int x;
  image_combo  = gtk_combo_box_text_new();
  static const char *img_formats[] = { PNG, JPG, BMP, TIFF };

  for (x = 0; x < 4; x++)
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(image_combo), img_formats[x], img_formats[x]);

  gtk_combo_box_set_active(GTK_COMBO_BOX(image_combo), 0);
  g_signal_connect(G_OBJECT(image_combo), "changed", G_CALLBACK(on_image_combo), NULL);
  gtk_grid_attach(GTK_GRID(grid), image_combo, POSITION_LEFT, 7, 1, 1);

  sdevice_lbl  = gtk_label_new(_(SDEVICE_LBL));
  gtk_grid_attach(GTK_GRID(grid), sdevice_lbl, POSITION_RIGHT, 6, 1, 1);

  sdev_combo   = gtk_combo_box_text_new();
  static const char *sdevices[] = { PNG16M, PNGALPHA, PNGGRAY, JPEG, JPEGCMYK, JPEGGRAY,
                                    BMP16M, BMPGRAY, TIFF24NC, TIFFGRAY };
  for (x = 0; x < 10; x++)
      gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(sdev_combo), sdevices[x], sdevices[x]);

  gtk_combo_box_set_active(GTK_COMBO_BOX(sdev_combo), 0);
  g_signal_connect(G_OBJECT(sdev_combo), "changed", G_CALLBACK(on_sdevice_combo), NULL);
  gtk_grid_attach(GTK_GRID(grid), sdev_combo, POSITION_RIGHT, 7, 1, 1);

  expand1      = gtk_expander_new(_(ANTI_ALIASING_LBL));
  gtk_grid_attach(GTK_GRID(grid), expand1, POSITION_LEFT, 8, 1, 1);

  alias_combo  = gtk_combo_box_text_new();
  static const char *alias_values[] = { "1", "2", "4" };

  for (x = 0; x < 3; x++)
      gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(alias_combo), alias_values[x], alias_values[x]);

  gtk_combo_box_set_active(GTK_COMBO_BOX(alias_combo), 2);
  gtk_container_add(GTK_CONTAINER(expand1), alias_combo);

  expand2      = gtk_expander_new(_(TRANSP_LBL));
  gtk_grid_attach(GTK_GRID(grid), expand2, POSITION_RIGHT, 8, 1, 1);

  trans_switch = gtk_switch_new();
  gtk_switch_set_active(GTK_SWITCH(trans_switch), TRUE);
  gtk_container_add(GTK_CONTAINER(expand2), trans_switch);

  button1_lbl  = gtk_label_new(_(SELECT_PDF_LBL));
  gtk_grid_attach(GTK_GRID(grid), button1_lbl, POSITION_LEFT, 9, POSITION_CENTER, 1);

  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button1_clicked), NULL);
  gtk_grid_attach(GTK_GRID(grid), button1, POSITION_LEFT, 10, POSITION_CENTER, 1);

  button2_lbl  = gtk_label_new(_(REUSE_LAST_PDF));
  gtk_grid_attach(GTK_GRID(grid), button2_lbl, POSITION_LEFT, 11, POSITION_CENTER, 1);

  button2      = gtk_button_new_with_label(_(BUTTONE_LBL));
  g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(on_button2_clicked), NULL);
  gtk_grid_attach(GTK_GRID(grid), button2, POSITION_LEFT, 12, POSITION_CENTER, 1);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(window);
  gtk_main();

  return EXIT_SUCCESS;
}

/* Re-use the last converted pdf */
void on_button2_clicked(void) {
  if (*last_pdf) {
    pdf_to_img(last_pdf);
  }
}


/* 
   return the last seperator '/' index number,
   we will use this index number to create our own
   `basename' alternative in C
*/
size_t index_last_sep(const char *str) {
  const char *ptr = str;
  size_t sep_index = 0 , x = 0;

  for (; *ptr; x++, ptr++)
    if ('/' == *ptr) {
      sep_index = x; /* keep in mind that we use loop */
    }

  return sep_index;
}


/* Show about dialog */
void on_about_clicked(void) {
  gtk_show_about_dialog(GTK_WINDOW(window),
                         "program-name", ABOUT_PROG_NAME,
                         "comments", _(ABOUT_COMMENTS),
                         "website", ABOUT_WEBSITE,
                         "website-label", _(ABOUT_WEBSITE_LABEL),
                         "license-type", GTK_LICENSE_GPL_3_0, NULL);
}


/* 
   Handle signal 'changed' from sdevice combobox
   and workaround the problem when setting
   different active item.
*/
void on_sdevice_combo(void) {
  unsigned char next = 0, current = 0;
  char *active = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(sdev_combo));

  if (STREQ(active,PNG16M))
      next = 0;
  else
    if (STREQ(active,PNGALPHA))
      next = 1;
    else
      if (STREQ(active,PNGGRAY))
        next = 2;
      else    /* 'active' not in png group */
      {
        current = 1; /* The jpg group */
        if (STREQ(active,JPEG))
          next = 3;
        else
          if (STREQ(active,JPEGCMYK))
            next = 4;
          else
            if (STREQ(active,JPEGGRAY))
              next = 5;
            else    /* 'active' not in jpg group */
            {
              current = 2; /* The bmp group */
              if (STREQ(active,BMP16M))
                next = 6;
              else
                if (STREQ(active,BMPGRAY))
                  next = 7;
                else    /* 'active' not in bmp group */
                {
                  current = 3; /* The tiff group */
                  next = (STREQ(active,TIFF24NC)) ? 8 : 9;
                }
            }
        }

  gtk_combo_box_set_active(GTK_COMBO_BOX(image_combo), current);
  gtk_combo_box_set_active(GTK_COMBO_BOX(sdev_combo), next);
}


/* Handle signal 'changed' from image format combobox */
void on_image_combo(void) {
  unsigned char current = 0;
  char *active = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(image_combo));

  if (STREQ(active,PNG)) {
    current = 0;
  } else {
    if (STREQ(active,JPG)) {
      current = 3;
    } else {
      current = (STREQ(active,BMP)) ? 6 : 8;
    }
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(sdev_combo), current);
}


/* File chooser dialog */
void on_button1_clicked(void) {
  int spin1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton1));
  int spin2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
  char *filename = NULL;

  if (spin1 > spin2) {
    RaiseWarning(_(REVERSED), _(REVERSED_BODY));
    return;
  }

  GtkWidget *chooser_dialog = gtk_file_chooser_dialog_new(_(SELECT_PDF_LBL),
                                                          GTK_WINDOW(window),
                                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                                          _(CANCEL_BTN),
                                                          GTK_RESPONSE_CANCEL,
                                                          _(CONVERT_BTN),
                                                          GTK_RESPONSE_ACCEPT, NULL);
  GtkFileFilter *filter_pdf = gtk_file_filter_new();
  gtk_file_filter_set_name(GTK_FILE_FILTER(filter_pdf),_(PDF_FILTER));
  gtk_file_filter_add_pattern(GTK_FILE_FILTER(filter_pdf), PDF_PATTERN);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser_dialog), GTK_FILE_FILTER(filter_pdf));

  if (GTK_RESPONSE_ACCEPT == gtk_dialog_run(GTK_DIALOG(chooser_dialog))) {
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser_dialog));
    snprintf(last_pdf, VLA, "%s", filename);
    pdf_to_img(filename);
  }
  gtk_widget_destroy(chooser_dialog);
}


/*
   In gtk2 the yellow warning icon is
   displayed but not in gtk3, because the
   devs behind gtk decided to deprecate
   all standard icons.
*/
void RaiseWarning(const char *str_to_warn1, const char *str_to_warn2) {
  GtkWidget *warn_dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK, 
                                                  "%s", str_to_warn1);
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(warn_dialog), "%s", str_to_warn2);
  gtk_dialog_run(GTK_DIALOG(warn_dialog));
  gtk_widget_destroy(warn_dialog);
}


/* 
   Remove the '.pdf' extension, 
   `gs' the formal parameter 'filename',
   create new folder if it doesn't exists and 
   rename the converted images to match the
   'from' and 'to' page range.
*/
void pdf_to_img(const char *filename) {
  char *im_combo = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(image_combo));
  char pdfname[VLA+1], BaseName[VLA+1], params[VLA+1];
  char ren1[VLA+1], ren2[VLA+1], created_dir[VLA+1];
  int spin1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton1));
  int spin2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
  int small_range = (spin2 - spin1) + 2, big_range = spin1, y = 0;
  size_t dirname_len = index_last_sep(filename), x = 0, z = 0;
  size_t fit = strlen(filename);
  size_t fit2 = fit - 4; /* exclude the .pdf file extension */
  struct stat DiR;

  if (1850 <= fit) {
    RaiseWarning(_(JOKE), _(FILENAME_TOO_LONG));
    return;
  }

  snprintf(pdfname, VLA, "%s", filename);

  for (z = 0, x = dirname_len+1; x < fit2; x++, z++)
    BaseName[z] = pdfname[x]; /* /path/to/some.pdf -> some      */
  BaseName[z] = '\0';

  if (240 < z) {
    RaiseWarning(_(RESOLUTION_WARN_TITLE), _(FILESYSTEM_LIMITS_BODY));
    return;
  }

  snprintf(created_dir, VLA, "%s converted", pdfname);
  stat(created_dir, &DiR);
  if (0 == S_ISDIR(DiR.st_mode)) {
    mkdir(created_dir, 0700);
  }

  snprintf(params, VLA, "gs -dBATCH -dNOPAUSE -dQUIET -dFirstPage=%d -dLastPage=%d "
                  "-sOutputFile=\"%s\"_pAge_%%01d.%s -sDEVICE=%s -r%d "
                  "-dGraphicsAlphaBits=%s -sBandListStorage=memory "
                  "-dBufferSpace=99000 -dNumRenderingThreads=1 %s\"%s\"",
    spin1, spin2, pdfname, im_combo,
    gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(sdev_combo)),
    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(entry)),
    gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(alias_combo)),
    gtk_switch_get_active(GTK_SWITCH(trans_switch)) ? "" : "-dNOTRANSPARENCY ", filename);
  system(params);

  for (y = 1; y < small_range; y++, big_range++) {
    snprintf(ren1, VLA, "%s_pAge_%d.%s", pdfname, y, im_combo);
    snprintf(ren2, VLA, "%s/%s_page_%d.%s", created_dir, BaseName, big_range, im_combo);
    rename(ren1, ren2);
  }
}
