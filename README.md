# futurehistory

#### Installation nach dem mergen einmalig folgende Befehle ausführen:

drush sql-dump > ../bck.sql

drush en -y features && drush en -y diff  && drush en -y fu_hilfetexte && drush en -y fu_ansicht && drush cc all

drush fd fu_hilfetexte && drush fd fu_ansicht

drush fr -y fu_hilfetexte &&drush fr -y fu_ansicht