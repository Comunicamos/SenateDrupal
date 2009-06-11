<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Bill Search' block
 */

/**
 *  Subject of the 'Senator Search' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_subject_bill_search() {
  return t('Legislative Bill Search:');
}

/**
 *  Display the content of the 'Bill Search' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_bill_search() {
  $output = '<Form Action="http://public.leginfo.state.ny.us/menugetf.cgi" method=post>
  <table>
	  <tr>
		  <td width="80"> <label for="QUERYDATA" style="width: 120px;">Bill number:</label> </td>
		  <td colspan="2"> <input type="text" id="QUERYDATA" name="QUERYDATA" style="width: 100px;"> </td>
	  </tr>
	  <tr>
	      <td> <label for="SESSYR" style="width: 120px;">Select year:</label> </td>
		  <td width="110"> <SELECT id="SESSYR" NAME="SESSYR" style="width: 105px;">Session
       <OPTION SELECTED VALUE="2009"> 2009
       <OPTION VALUE="2008"> 2008
       <OPTION VALUE="2007"> 2007
       <OPTION VALUE="2006"> 2006
       <OPTION VALUE="2005"> 2005
       <OPTION VALUE="2004"> 2004
       <OPTION VALUE="2003"> 2003
       <OPTION VALUE="2002"> 2002
       <OPTION VALUE="2001"> 2001
       <OPTION VALUE="2000"> 2000
       <OPTION VALUE="1999"> 1999
       <OPTION VALUE="1998"> 1998
       <OPTION VALUE="1997"> 1997
       <OPTION VALUE="1996"> 1996
       <OPTION VALUE="1995"> 1995
</SELECT> </td>
       <td> <input type="submit" value="Status"> </td>
	  </tr>
  </table>



 <input type=hidden name="referer" value="http://www.nyssenate11.com">
 <input type="hidden" name="COMMONQUERY" value="">
 <input type="hidden" name="SCRSZ" value="">
 <input type="hidden" name="TOKEN" value="">
 
<!--Begin Legislative Session Information section list. -->
<!--Please replace link references to work with your code. -->
</form>';

  return $output;
}
