#ifndef SEMESTRAL_WORK_PROCESSABLE_HPP
#define SEMESTRAL_WORK_PROCESSABLE_HPP

#define PROCESS_OK 1
#define PROCESS_EXIT 2
#define PROCESS_BACK 3

class Processable {
public:
  virtual int process () = 0;  // `= 0` makes this class abstract
};

#endif //SEMESTRAL_WORK_PROCESSABLE_HPP
