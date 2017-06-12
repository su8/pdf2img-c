AM_CPPFLAGS = \
    -DLOCALEDIR=\"$(datadir)/locale\" \
    -DPROGRAM_ICON=\"$(datadir)/pixmaps/pdf2img_c_icon.xpm\" \
    -DGETTEXT_PACKAGE=\"pdf2img\" \
    -DSHOW_IMAGES_ON_BUTTONS=$(SHOW_BTN_IMGS) \
    -DDECORATE_VIA_CUSTOM_CSS=$(CUSTOM_CSS)

bin_PROGRAMS = \
    pdf2img

pdf2img_CFLAGS = \
    $(gtk_CFLAGS) \
    -Wall -Wextra -O2

pdf2img_LDADD = \
    $(gtk_LIBS)

pdf2img_SOURCES = gettext.h main.c my_constants.h
