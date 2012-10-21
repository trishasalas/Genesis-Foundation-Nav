<?php
/*
Plugin Name: Genesis Foundation Nav
Plugin URI: http://wpconsult.net/
Description: Converts your dropdown nav menu to a fully responsive nav based on Foundation
Author: pauldewouters
Author URI: http://wpconsult.net/
Version: 0.1
Text Domain: genesis-foundation-nav
License: GPL version 2 or later - http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
*/

if(!defined('GFN_PLUGIN_DIR'))
	define( 'GFN_PLUGIN_DIR', trailingslashit(plugin_dir_path(__FILE__) ));

if(!defined('GFN_PLUGIN_URL'))
	define( 'GFN_PLUGIN_URL', plugin_dir_url(__FILE__) );


require_once GFN_PLUGIN_DIR . 'inc/class.GenesisFoundationNav.inc';

new GenesisFoundationNav();