<?php

/**
 * An array of form elements
 * 
 * @return array 
 */
function simple_subscription_subscribe_form() {
  $form = array();
  
  $form['firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('Firstname'),
    '#maxlength' => 64,
    '#required' => true
  );
  
  $form['lastname'] = array(
    '#type' => 'textfield',
    '#title' => t('Lastname'),
    '#maxlength' => 64,
    '#required' => true
  );
  
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#maxlength' => 64,
    '#required' => true
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Register'),
  );
  
  return $form;
}

/**
 * Validation handler for simple_registration_register_form()
 *
 * @param array $form
 * @param array $form_state
 */
function simple_subscription_subscribe_form_validate($form, &$form_state) {
  $email = $form_state['values']['email'];  
  if(!valid_email_address($email)) {
    form_set_error('email', 'Please provide a valid email address');
  }
  
  if(simple_registration_email_is_in_use($email)) {
    form_set_error('email', 'Email is already registered');
  }
}

/**
 * Submit handler for simple_registration_register_form()
 *
 * @param type $form
 * @param type $form_state
 */
function simple_subscription_subscribe_form_submit($form, &$form_state) {
  $firstname = strip_tags($form_state['values']['firstname']);
  $lastname  = strip_tags($form_state['values']['lastname']);
  $email     = strip_tags($form_state['values']['email']);
  
  db_insert('simple_subscription')
  ->fields( 
      array(
        'firstname' => $firstname, 
        'lastname' => $lastname, 
        'email' => $email 
      ) 
    )
  ->execute();
  
  drupal_set_message('Congratulations! You have successfully subscribed.');
}

/**
 * Validates if the email is already registered to another subscriber
 * @param string $email
 * @return boolean
 */
function simple_registration_email_is_in_use($email) {
  if(!empty($email)) {
    $result = db_select('simple_subscription','ss')
      ->fields('ss', array('email'))
      ->condition('email', $email, '=')
      ->execute()
      ->fetchField();
    
    if($result) return true;
  }
  return false;
}