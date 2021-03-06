#ifndef __BANKING_H
#define __BANKING_H

class Banking {
  std::list<Account> accounts;
  public:
  void addAccount(std::string, std::string, double);
  void addAccount(const Account& ref);
  void removeAccount(int id);
  void displayAll();
  Account* findById(int id);
  double findAverageBalance();
  Account* findAccountWithMaxBalance();
  int countAccountsByRange(double,double);
  int countAccountsByBalanceLimit(double);
  std::list<Account> findAccountsByName(std::string name);
};

void Banking::addAccount(std::string id, std::string name, double bal) {
  //Account temp(id,name,bal);
  //accounts.push_back(temp);                        //method-1
  accounts.push_back(Account(id,name,balance));       //method-2
  //accounts.emplace_back(id,name,balance);          //method-3, only from C++11
}

void Banking::addAccount(const Account& ref) {
  accounts.push_back(ref);
}

void Banking::displayAll() {
  std::list<Account>::iterator iter;
  for(iter=accounts.begin();iter!=accounts.end();++iter)
      iter->display();
  //for(auto& ref:accounts)
  //    ref.display();
}
Account* findById(int id) {
  std::list<Account>::iterator iter;
  for(iter=accounts.begin();iter!=accounts.end();++iter)
    if(iter->getId()==id)
        return &(*iter);    // break;
  return NULL;  //if(iter==accounts.end()) return NULL; 
}
double findAverageBalance() {
  double sum=0;
  std::list<Account>::iterator iter;
  for(iter=accounts.begin();iter!=accounts.end();++iter)
    sum += iter->getBalance();
  return sum/accounts.size();
}
Account& findAccountWithMaxBalance(int id) {
  std::list<Account>::iterator iter=accounts.begin();
  double maxbal = iter->getBalance();
  auto maxIter = iter;
  ++iter;
  for(;iter!=accounts.end();++iter)
    if(iter->getBalance()>maxbal) {
        maxbal = iter->getBalance;
        maxIter = iter;
    }
  return *maxIter;
} 
int Banking::countAccountsByRange(double minval,double maxval) {
  int count=0;
  /*std::list<Account>::iterator iter;
  for(iter=accounts.begin();iter!=accounts.end();++iter)
    if(iter->getBalance() >= minval && iter->getBalance() <= maxval)
       count++;*/
  count=std::count_if(accounts.begin(), accounts.end(),
                                [minval,maxval](const Account& ref) {
    return ref.getBalance() > minval && ref.getVal() <= maxval;
  });
                                        
  return count;
}
bool mycompare(const Account& ref) {
  if(ref.getBalance() > MIN_LIMIT) 
    return true;
  else
    return false;
}
int Banking::countAccountsWithMinBal(double minval) {
  int count=0;
  /*std::list<Account>::iterator iter;
  for(iter=accounts.begin();iter!=accounts.end();++iter)
    if(iter->getBalance() >= minval)
       count++;*/
  //count = std::count_if(accounts.begin(), accounts.end(), mycompare);
  count = std::count_if(accounts.begin(), accounts.end(), 
                                    [minval](const Account& ref) {
    return ref.getBalance() > minval;
  });
  return count;
}
bool bcompare(const Account& r1, const Account& r2) {
    return r1.getBalance() < r2.getBalance();
}
void Banking::sortByBalance() {
   //std::sort(accounts.begin(), accounts.end(), bcompare);
   std::sort(accounts.begin(), accounts.end(), 
                [](const Account& r1, const Account& r2) {
    return r1.getBalance() < r2.getBalance();
   });
}
int Banlking::countAccountsByBalanceLimit(double) {
  //TODO
}
double Banking::findAccountWithMaBalance() {

  auto iter = std::maxval(accounts.begin(), accounts.end(), 
                [](const Account& r1, const Account& r2) {
                    return r1.getBalance() < r2.getBalance();
   });
}
std::list<Account> Banking::findAccountsByName(std::string name) {
   std::list<Account> results;
   std::list<Account>::iterator iter;
   for(iter=accounts.begin();iter!=accounts.end();++iter)
       if(iter->getName()==name) //TODO: case insensitive, sub string
          results.push_back(*iter);
    return results;   //Possible scope of NRVO
}

#endif


/** Test code
    std::list<Account> matchingAccounts = banking.findAccountsByName("scott");
    
    Better alternative to collect multiple accounts:-
    void Banking::fetchAccountsByName(std::string name,
                            std::list<Account>&results);
    banking.fetchAccountsByName("scott", matchingAccounts);
*/
    

