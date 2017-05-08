#!/usr/bin/env bash

git pull origin master
cd ../../themes/future_history/ && git pull origin master && cd -
cd ../futurehistory/ && git pull origin master && cd -
drush cc all


drush cc all
drush dis -y overlay
drush en -y map_view_update
drush fr -y map_view_update

drush cc all
