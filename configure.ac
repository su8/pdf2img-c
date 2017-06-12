# This file is processed by autoconf to create a configure script
AC_INIT([pdf2img], 1.6)
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign subdir-objects dist-xz no-dist-gzip])

AC_PROG_CC
AC_PROG_CC_STDC

AC_ARG_ENABLE(button-images,
  AC_HELP_STRING(
    [--enable-button-images],
    [show images on buttons. [default=disable]]
  ), [enable_imgs=$enableval])

if test "$enable_imgs" = yes; then
    SHOW_BTN_IMGS=1
else
    SHOW_BTN_IMGS=0
fi
AC_SUBST(SHOW_BTN_IMGS)

AC_ARG_ENABLE(custom-css,
  AC_HELP_STRING(
    [--enable-custom-css],
    [use custom css. [default=disable]]
  ), [enable_css=$enableval])

if test "$enable_css" = yes; then
    CUSTOM_CSS=1
else
    CUSTOM_CSS=0
fi
AC_SUBST(CUSTOM_CSS)

IT_PROG_INTLTOOL([0.40.0])

GETTEXT_PACKAGE=pdf2img
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT

PKG_CHECK_MODULES(gtk, gtk+-3.0)

rm -f po/LINGUAS
for po_file in `ls --color=never po/*.po | sort`; do 
  echo $po_file | gawk -F '.' '{gsub("po/","");print $1}' >> po/LINGUAS
done

AC_CONFIG_FILES([
Makefile
src/Makefile
pdf2img.desktop
po/Makefile.in
])


AC_OUTPUT

echo
echo 'Now type "make" and "sudo make install" afterwards'
echo
