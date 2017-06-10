#ifndef SEMESTRAL_WORK_COLORPAIRGENERATOR_HPP
#define SEMESTRAL_WORK_COLORPAIRGENERATOR_HPP

/**
 * This static-like class serves the purpose of ncurses color pairs overlapping.
 * This class initializes ncurses color pairs using a static counter.
 */
class ColorPairGenerator {
public:
  /**
   * Add initialization of ncurses color.
   * @param text color of a text
   * @param background color of a text background
   * @return number of color pair
   */
  static short addColor (short text, short background);

private:
  /**
   * Static counter of ncurses pair number.
   */
  static short counter;

  /**
   * This method makes impossible to create an instance of this class.
   */
  ColorPairGenerator ();
};

#endif // SEMESTRAL_WORK_COLORPAIRGENERATOR_HPP
