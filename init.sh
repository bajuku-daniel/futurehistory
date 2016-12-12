#!/usr/bin/env bash

#git pull origin dev

## delete menu link 626 :)
#drush ev "menu_link_delete(626);"
#drush ev "module_load_include('inc', 'locale', 'menu');menu_link_delete(626);"
#
#drush dl -y strongarm
#drush en -y strongarm
#drush dl -y features
#drush en -y features
#drush dl -y diff
#drush en -y diff
#drush dl autocomplete_deluxe
#drush en -y autocomplete_deluxe
#drush dl field_placeholder 7.x-1.0
#drush en -y field_placeholder
#drush en -y fu_hilfetexte
#drush en -y fu_ansicht
#
#
#drush cc all
#
#drush fr -y fu_hilfetexte
#drush fr -y fu_ansicht
#
#drush user-password rafael --password="rafael_fuhi_2016"
#drush user-create test --mail="test@test.com" --password="test"
#
#cp patches/autocomplete_deluxe-fix_suggestion_order-2360761-1.patch ../autocomplete_deluxe/autocomplete_deluxe-fix_suggestion_order-2360761-1.patch
#cd .. && cd autocomplete_deluxe && patch < autocomplete_deluxe-fix_suggestion_order-2360761-1.patch


cp patches/autocomplete_deleuxe-term-count.patch ../autocomplete_deluxe/autocomplete_deleuxe-term-count.patch
cd .. && cd autocomplete_deluxe && patch < autocomplete_deleuxe-term-count.patch
drush cc all