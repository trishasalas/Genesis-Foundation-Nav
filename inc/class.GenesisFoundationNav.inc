<?php
/**
 * class.GenesisFoundationNav.inc.php
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

require 'foundation-walker.php';

class GenesisFoundationNav {

	function __construct() {

		// Output the nav menu in the theme location
		add_filter( 'wp_nav_menu_args', array( &$this, 'custom_nav_menu_args' ) );

		if ( 'genesis' == basename( TEMPLATEPATH ) ) {
			// Remove Genesis Nav wrapper divs
			add_filter( 'genesis_do_nav', array( &$this, 'remove_structural_wraps' ), 15, 3 );

			add_action( 'after_setup_theme', array( &$this, 'move_menu' ) );
		}

		add_filter( 'wp_nav_menu_objects', array( &$this, 'add_parent_class' ) );
		add_filter( 'wp_nav_menu_objects', array( &$this, 'add_active_class' ) );

		add_action( 'wp_enqueue_scripts', array( &$this, 'load_styles' ) );
		add_action( 'wp_enqueue_scripts', array( &$this, 'load_scripts' ) );

		add_action( 'wp_enqueue_scripts', array( &$this, 'disable_scripts' ), 100 );
	}

	function custom_nav_menu_args( $args ) {

		// Define nav menu args
		if ( $args['theme_location'] == 'primary' ) {
			$args['container']       = 'nav';
			$args['container_class'] = 'top-bar';
			$args['menu_id']         = 'foundation-menu';
			$title                   = '<ul><li class="name"><h1><a href="#">' . get_bloginfo('name') . '</a></h1></li><li class="toggle-topbar"><a href="#"></a></li></ul>';
			$args['items_wrap']      = $title . '<section><ul class="left"><li class="divider"></li>%3$s</ul></section>';
			$args['walker']          = new Foundation_Walker();
		} //end if
		return $args;
	}

	function remove_structural_wraps( $nav_output, $nav, $args ) {

		return $nav;
	}

	function move_menu() {
		remove_action( 'genesis_after_header', 'genesis_do_nav' );
		add_action( 'genesis_before', 'genesis_do_nav' );
	}

	function hasSub( $menu_item_id, $items ) {
		foreach ( $items as $item ) {
			if ( $item->menu_item_parent && $item->menu_item_parent == $menu_item_id ) {
				return true;
			}
		}
		return false;
	}

	function add_parent_class( $items ) {
		foreach ( $items as $item ) {
			if ( $this->hasSub( $item->ID, $items ) ) {
				$item->classes[] = 'has-dropdown'; // all elements of field "classes" of a menu item get join together and render to class attribute of <li> element in HTML
			}
		}
		return $items;
	}

	function add_active_class( $items ) {
		foreach ( $items as $item ) {
			$current_element_markers = array( 'current-menu-item', 'current-menu-parent', 'current-menu-ancestor' );
			$current_class           = array_intersect( $current_element_markers, $item->classes );
			if ( ! empty( $current_class ) ) {
				$item->classes[] = 'active'; // all elements of field "classes" of a menu item get join together and render to class attribute of <li> element in HTML
			}
		}
		return $items;
	}

	function load_styles() {
		wp_enqueue_style( 'foundation', plugins_url( '/css/styles.css', __FILE__ ) );
	}

	function load_scripts() {

		wp_enqueue_script( 'foundation-topbar', plugins_url( '/js/jquery.foundation.topbar.js', __FILE__ ), array( 'jquery' ) );
		wp_enqueue_script( 'gfn-plugin', plugins_url( '/js/plugin.js', __FILE__ ), array( 'jquery', 'foundation-topbar' ) );
	}

	function disable_scripts() {
		if ( 'genesis' == basename( get_template_directory() ) ) {
			wp_dequeue_script( 'superfish' );
			wp_dequeue_script( 'superfish-args' );
		}

		if ( 'twentytwelve' == basename( get_template_directory() ) ) {
			wp_dequeue_script( 'twentytwelve-navigation' );
		}
	}
}