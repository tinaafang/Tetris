#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>

class Observer;

class Subject
{
  std::vector<Observer *> observers;

public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers(bool over);
  void clear();
  void notifyObserversPrompt();
  virtual char getState(int player, int row, int col) const = 0;
  virtual int getLevel(int player) const = 0;
  virtual int getScore(int player) const = 0;
  virtual int getBonus(int player) const = 0;
  virtual bool getOver(int player) const = 0;
  virtual int getHiScore() const = 0;
  virtual std::string getName(int player) const = 0;
  virtual bool getChange(int player, int row, int col) const = 0;
  virtual void setChange(int player, int row, int col, bool change) = 0;
  virtual ~Subject() = default;
};

#endif
