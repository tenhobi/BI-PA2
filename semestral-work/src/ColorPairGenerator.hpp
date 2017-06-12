#ifndef SEMESTRAL_WORK_COLORPAIRGENERATOR_HPP
#define SEMESTRAL_WORK_COLORPAIRGENERATOR_HPP

/**
 * Static-like class which serves the purpose of overpower the ncurses color pairs overlapping.
 * Uses static-like generator of pairs.
 */
class ColorPairGenerator {
public:
  /**
   * Add initialization of ncurses color.
   *
   * @param text color of a text
   * @param background color of a text background
   *
   * @return number of the new color pair
   */
  static short addColor (short text, short background);

protected:
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
