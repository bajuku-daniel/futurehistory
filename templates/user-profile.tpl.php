<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */

global $user;
$currentUser = $user->uid;
//get profile url for that you can use $user_id as user id
$profileUrl = arg(1);
// compare usernames to determine whether the user is on their own profile.
if ($currentUser == $profileUrl) {
  //user is on their profile, display link
  $myAccount = 1;
}
else {
  $myAccount = 0;
}

?>



<div class="row">

  <div class="col-sm-3 col-sm-offset-1 blog-sidebar">
    <div class="sidebar-module sidebar-module-inset">
      <div class="profile"<?php print $attributes; ?>>
        <?php print render($user_picture); ?>
      </div>
      <?php if ($myAccount): ?>
        <a class="btn btn-default profile-edit-button"
           href="/user/<?php print($currentUser); ?>/edit">Profil Bearbeiten </a>
      <?php endif ?>
    </div>

  </div><!-- /.blog-sidebar -->

  <div class="col-sm-8 blog-main">
    <div class="blog-post">
      <h4>Benutzer Informationen</h4>
      <?php print render($user_profile); ?>
    </div>

    <div class="blog-post">
      <h4>Benutzer Aktivität</h4>
      <?php print $user_activity; ?>
    </div>

    <div class="blog-post">
      <h4>Die letzten Ansichten</h4>
      <?php print $user_last_views; ?>
    </div>
  </div><!-- /.blog-main -->

</div>



