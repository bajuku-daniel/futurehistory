#!/usr/bin/env bash

git pull origin dev

#delete menu link 626 :)
drush ev "menu_link_delete(626);"
drush ev "module_load_include('inc', 'locale', 'menu');menu_link_delete(626);"

drush dl -y features
drush en -y features
drush dl -y diff
drush en -y diff
drush en -y fu_hilfetexte
drush en -y fu_ansicht

drush cc all

drush fr -y fu_hilfetexte
drush fr -y fu_ansicht
