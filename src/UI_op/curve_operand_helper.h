#ifndef WKY_CURVE_OPERAND_H
#define WKY_CURVE_OPERAND_H

namespace framework {
    namespace scene {
        class trimesh;
    }
}

class curve_operand_helper
{
private:
    void draw_control_points(const framework::scene::trimesh* triangle_mesh);

public:
    void clear_curve();
    void fit_curve(bool is_loop);
    void update_curve();

    static curve_operand_helper* get_instance();
};

#endif
