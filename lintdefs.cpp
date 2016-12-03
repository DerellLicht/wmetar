//lint -esym(40, __INT_MAX__)

//  go back and fix this later
//lint -e10  Expecting '}'

//lint -e650  Constant '4294967146' out of range for operator 'case'
//lint -e818  Pointer parameter could be declared as pointing to const
//lint -e840  Use of nul character in a string literal (is common in Windows controls)
//lint -e843  Variable could be declared as const
//lint -e845  The right argument to operator '|' is certain to be 0 
//lint -e1066 Symbol declared as "C" conflicts with line 60, file ..\der_libs\statbar.h
//lint -e1709 typedef 'Runway_VisRange' declared as "C" 'conflicts with ...

//lint -e1776 Converting a string literal to char * is not const safe (initialization)

//lint -e774  Boolean within 'right side of && within if' always evaluates to True

//lint -e525  Negative indentation from line ...
//lint -e539  Did not expect positive indentation from line ...
//lint -e534  Ignoring return value of function

//lint -e769  global enumeration constant not referenced
//lint -e768  global struct member not referenced
//lint -e749  local enumeration constant not referenced
//lint -e755  global macro not referenced

//lint -e736  Loss of precision (assignment) (64 bits to 32 bits) (double to float)
//lint -e713  Loss of precision (unsigned long to int)
//lint -e732  Loss of sign (arg. no. 3) (int to unsigned long)
//lint -e737  Loss of sign in promotion from int to unsigned long

//  bypass library functions
//lint -esym(714, resize_window, ShellGetPath, get_file_datetime)
//lint -esym(759, resize_window, ShellGetPath, get_file_datetime)
//lint -esym(765, resize_window, ShellGetPath, get_file_datetime)
//lint -esym(1714, CStatusBar::set_statusbar_font, CVListView::recalc_dx, CVListView::hide_horiz_scrollbar)
//lint -esym(1714, CVListView::HitTest, CVListView::GetItemState, CVListView::insert_column_header)
//lint -esym(1714, CVListView::delete_column, CTerminal::resize_terminal_pixels)
//lint -esym(1714, CTerminal::get_terminal_dimens, CTerminal::copy_list_to_clipboard, CTerminal::put)

//lint -esym(1704, CThread::CThread)
//lint -esym(1719, CThread)
//lint -esym(1720, CThread)
//lint -esym(1721, CThread)
//lint -esym(1722, CThread)

