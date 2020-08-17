#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation {
  public:
    Animation();
    Animation(int index, int numFrames, int animationSpeed);

    unsigned int index;
    unsigned int numFrames;
    unsigned int animationSpeed;


};

#endif // ANIMATION_HPP
