<?php

/**
 * @file
 *
 * Callbacks and functions used in the Delete Form Page.
 */

/**
 * Get the Delete Page Form.
 * 
 * @param array $form_state
 *   The Drupal Form State.
 * @param string $form_name
 *   The name of the form to delete.
 * 
 * @return array
 *   The Drupal Form.
 */
function xml_form_builder_delete(array &$form_state, $form_name) {
  module_load_include('inc', 'xml_form_builder', 'XMLFormDatabase');
  if (!XMLFormDatabase::Exists($form_name)) {
    drupal_set_message(t('Form "%name" does not exist.', array('%name' => $form_name)), 'error');
    drupal_not_found();
    exit();
  }
  return array(
    'form_name' => array(
      '#type' => 'hidden',
      '#value' => $form_name,
    ),
    'description' => array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#value' => t('Are you sure you want to delete the form <b>%name</b>. This action is irreversible.', array('%name' => $form_name)),
      '#suffix' => '</div>',
    ),
    'delete' => array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#name' => 'delete'
    ),
    'cancel' => array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#name' => 'cancel'
    ),
  );
}

/**
 * Submit the delete form. Deletes a Form definition within the database.
 * 
 * Returns the user to the main menu.
 * 
 * @param array $form
 *   The Drupal Form.
 * @param array $form_state 
 *   The Drupal Form State.
 */
function xml_form_builder_delete_submit(array $form, array &$form_state) {
  if ($form_state['clicked_button']['#name'] == 'delete') {
    module_load_include('inc', 'xml_form_builder', 'XMLFormDatabase');
    $form_name = $form_state['values']['form_name'];
    if (XMLFormDatabase::Delete($form_name)) {
      drupal_set_message(t('Successfully deleted form "%name".', array('%name' => $form_name)));
    }
    else {
      drupal_set_message(t('Failed to deleted form "%name".', array('%name' => $form_name)), 'error');
    }
  }
  $form_state['redirect'] = MENU_XML_FORM_BUILDER_MAIN;
}