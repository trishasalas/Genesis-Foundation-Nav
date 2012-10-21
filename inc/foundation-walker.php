<?php
/**
 * foundation-walker.php
 *
 * Description of the purpose of this file
 *
 * @package     Project name
 * @since       Version number
 * @link        http://github.com/pdewouters/repository
 * @author      Paul de Wouters
 * @copyright   Copyright (c) 2012, Paul de Wouters
 * @license     http://opensource.org/licenses/gpl-2.0.php GNU Public License
 */

class Foundation_Walker extends Walker_Nav_Menu{
// add classes to ul sub-menus
	function start_lvl( &$output, $depth = 0, $args = array() ) {
		$indent = str_repeat("\t", $depth);
		$output .= "\n$indent<ul class=\"dropdown\">\n";
	}

	function end_el( &$output, $item, $depth = 0, $args = array() ) {
		if($depth == 0)
		$output .= "</li>\n<li class=\"divider\"></li>\n";
		else
		$output .= "</li>\n";
	}
}