/*
   Copyright 12/17/2014
 
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

/* protection against multiple inclusions */
#ifndef MY_CONSTANTS_H_
#define MY_CONSTANTS_H_

#define POSITION_LEFT 1
#define POSITION_RIGHT 2
#define POSITION_CENTER 2
#define RESOLUTION_LBL "DPI Resolution"
#define RESOLUTION_NUM "100"
#define RESOLUTION_WARN_TITLE "WARNING !"
#define SELECT_PDF_LBL "Select PDF file"
#define ABOUT_LBL "About"
#define FROM_LBL "From page:"
#define IMG_LBL "Image format"
#define SDEVICE_LBL "sDevice"
#define TO_LBL "To:"
#define BUTTONE_LBL "Click here"
#define REUSE_LAST_PDF "Re-use the last pdf"
#define REVERSED "Reversed Numbers"
#define EMPTY_RES_TITLE "Hold on cowboy!"
#define EMPTY_RES_BODY "You cannot leave\nthe \"Resolution\" empty"
#define REVERSED_BODY "\"From page\" cannot be\ngreater than \"To\""
#define DETECTED_CHARS_BODY "Please remove \"%s\""
#define FILESYSTEM_LIMITS_BODY "You are about to exceed the\nfilesystem limits, please shorten\nthe PDF filename."
#define JOKE "Official letter:"
#define FILENAME_TOO_LONG "The given filename is over 1900\ncharacters long ?!"
#define PDF_FILTER "PDF Filter"
#define PDF_PATTERN "*.pdf"
#define CANCEL_BTN "Cancel"
#define CONVERT_BTN "Convert"
#define ANTI_ALIASING_LBL "Antialiasing"
#define TRANSP_LBL "GS Transparency"
#define PNG "png"
#define JPG "jpg"
#define BMP "bmp"
#define TIFF "tiff"
#define PNG16M "png16m"
#define PNGALPHA "pngalpha"
#define PNGGRAY "pnggray"
#define JPEG "jpeg"
#define JPEGCMYK "jpegcmyk"
#define JPEGGRAY "jpeggray"
#define BMP16M "bmp16m"
#define BMPGRAY "bmpgray"
#define TIFF24NC "tiff24nc"
#define TIFFGRAY "tiffgray"
#define PROGRAM_TITLE "PDF to IMG"
#define ABOUT_PROG_NAME "pdf2img"
#define ABOUT_WEBSITE "https://wifiextender.github.io"
#define ABOUT_WEBSITE_LABEL "Developers website"
#define ABOUT_COMMENTS "Convert easily PDF to multiple images\nin various formats with a single mouse click"

#define APP_CSS "GtkWindow {"\
            "color: #ec7c45;"\
            "background: black;"\
        "}"\
        "GtkGrid {"\
            "background: black;"\
        "}"\
        "GtkSwitch {"\
            "background: silver;"\
            "border-radius: 10px;"\
            "border: none;"\
            "box-shadow: 0 0 13px #333 inset;"\
        "}"\
        "GtkFileChooser {"\
            "background: black;"\
            "border-radius: 10px;"\
            "border: none;"\
            "color: #ec7c45;"\
        "}"\
        "GtkEntry {"\
            "background: darkgrey;"\
            "border-radius: 10px;"\
            "border: none;"\
            "color: black;"\
        "}"\
        "GtkEntry:hover {"\
            "color: white;"\
            "box-shadow: 0 0 13px #333 inset;"\
        "}"\
        "GtkEntry:focused {"\
            "background: silver;"\
        "}"\
        "GtkAboutDialog {"\
            "background: black;"\
            "border-radius: 10px;"\
            "border: none;"\
            "color: #ec7c45;"\
        "}"\
        "GtkButton {"\
            "color: black;"\
            "border-radius: 10px;"\
            "border: none;"\
         "}"\
        "GtkButton:hover {"\
            "background: grey;"\
            "color: white;"\
            "box-shadow: 0 0 13px #333 inset;"\
            "transition: 400ms linear;"\
        "}"\
        "GtkMessageDialog {"\
            "background: black;"\
            "border-radius: 10px;"\
            "border: none;"\
            "color: white;"\
        "}"\
        "GtkExpander {"\
            "border-radius: 10px;"\
            "border: none;"\
            "background-color: grey;"\
            "color: #ec7c45;"\
        "}"

#endif /* MY_CONSTANTS_H_ */
