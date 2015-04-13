class StrategyHuman: public Player{
public:
  std::string chooseCountryToReinforce();
  int chooseNumberToReinforce();

  std::string chooseSourceFortificationCountry();
  std::string chooseDestinationFortificationCountry();
  int chooseNumberOfFortificationArmies();

  std::string chooseAttackingCountry();
  std::string chooseDefendingCountry();
  bool chooseContinueAttack();
 
private:
  
}