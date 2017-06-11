#ifndef SEMESTRAL_WORK_PROCESSABLE_HPP
#define SEMESTRAL_WORK_PROCESSABLE_HPP

#define PROCESS_OK 1
#define PROCESS_EXIT 2
#define PROCESS_BACK 3

/**
 * Super abstract class which provides an interface for processable objets.
 */
class Processable {
public:
  /**
   * Virtual destructor.
   */
  virtual ~Processable ();

  /**
   * Processes some job and then returns one of the process status code.
   *
   * @return process status code.
   */
  virtual int process () = 0;  // `= 0` makes this class abstract
};

#endif //SEMESTRAL_WORK_PROCESSABLE_HPP
