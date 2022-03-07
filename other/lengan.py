from manim import *

class Lengan(LinearTransformationScene):
    def __init__(self):
        LinearTransformationScene.__init__(
            self,
            show_coordinates=False,
            leave_ghost_vectors=False,
            show_basis_vectors=False
        )

    def construct(self):
        forearm = Square()
        forearm.set_stroke(BLUE_B, opacity=1.0)
        forearm.set_fill(BLUE_B, opacity=1.0)

        self.play(DrawBorderThenFill(forearm))
        matrix = [[1, 0], [0, 0.2]]
        self.play(forearm.animate.apply_matrix(matrix))
        self.play(forearm.animate.shift(RIGHT))
        self.play(Rotate(forearm, angle=PI/3, about_point=ORIGIN, rate_func=smooth))
        self.play(forearm.animate.shift(RIGHT))

        arm = Square()
        arm.set_stroke(BLUE_B, opacity=1.0)
        arm.set_fill(BLUE_B, opacity=1.0)

        self.play(DrawBorderThenFill(arm))
        self.play(arm.animate.apply_matrix(matrix))

        whole_arm = Group(forearm, arm) 
        self.play(whole_arm.animate.shift(RIGHT))
        self.play(Rotate(whole_arm, angle=-PI/6, about_point=ORIGIN, rate_func=smooth))
        self.play(whole_arm.animate.shift(LEFT))


        self.wait()