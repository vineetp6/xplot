/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_MARKS_HPP
#define XPLOT_MARKS_HPP

#include <map>
#include <string>
#include <vector>

#include "xtl/xoptional.hpp"

#include "xwidgets/xholder_id.hpp"
#include "xwidgets/xwidget.hpp"

#include "xboxed_container.hpp"
#include "xplot.hpp"
#include "xscales.hpp"

namespace xpl
{
    inline const std::vector<color_type>& category10()
    {
        static const std::vector<color_type> category = {
            "#1f77b4",
            "#ff7f0e",
            "#2ca02c",
            "#d62728",
            "#9467bd",
            "#8c564b",
            "#e377c2",
            "#7f7f7f",
            "#bcbd22",
            "#17becf"
        };
        return category;
    }

    /*********************
     * xmark declaration *
     *********************/

    using xmark_scales_type = std::map<std::string, xw::xholder<xscale>>;
    using xmark_tooltip_type = xw::xholder<xw::xwidget>;

    template <class D>
    class xmark : public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;
        using scales_type = xmark_scales_type;
        using preserve_domain_type = std::map<std::string, bool>;
        using labels_type = std::vector<std::string>;
        using selected_type = std::vector<xtl::xoptional<int>>;
        using tooltip_type = xtl::xoptional<xmark_tooltip_type>;

        xmark();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(scales_type, derived_type, scales);
        XPROPERTY(::xeus::xjson, derived_type, scales_metadata);
        XPROPERTY(preserve_domain_type, derived_type, preserve_domain);
        XPROPERTY(bool, derived_type, display_legend);
        XPROPERTY(labels_type, derived_type, labels);
        XPROPERTY(bool, derived_type, apply_clip, true);
        XPROPERTY(bool, derived_type, visible, true);
        XPROPERTY(::xeus::xjson, derived_type, selected_style, ::xeus::xjson::object());
        XPROPERTY(::xeus::xjson, derived_type, unselected_style, ::xeus::xjson::object());
        XPROPERTY(selected_type, derived_type, selected);
        XPROPERTY(tooltip_type, derived_type, tooltip);
        XPROPERTY(::xeus::xjson, derived_type, tooltip_style, ::xeus::xjson::object());
        XPROPERTY(bool, derived_type, enable_hover, true);
        XPROPERTY(::xeus::xjson, derived_type, interactions);
        XPROPERTY(X_CASELESS_STR_ENUM(mouse, center), derived_type, tooltip_location, "mouse");

    private:

        void set_defaults();
    };

    /**********************
     * xlines declaration *
     **********************/

    template <class D>
    class xlines : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;
        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using opacities_type = std::vector<double>;
        using curves_subset_type = std::vector<int>;

        template <class XS, class YS>
        xlines(XS&&, YS&&);

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(data_type, derived_type, x);
        XPROPERTY(data_type, derived_type, y);
        XPROPERTY(colors_type, derived_type, color);
        XPROPERTY(colors_type, derived_type, colors, category10());
        XPROPERTY(colors_type, derived_type, fill_colors);
        XPROPERTY(double, derived_type, stroke_width, 2.0);
        XPROPERTY(X_CASELESS_STR_ENUM(none, labels), derived_type, labels_visibility, "none");
        XPROPERTY(curves_subset_type, derived_type, curves_subset);
        XPROPERTY(X_CASELESS_STR_ENUM(solid, dashed, dotted, dash_dotted), derived_type, line_style, "solid");
        XPROPERTY(X_CASELESS_STR_ENUM(linear, basis, basis-open, basis-closed, bundle, cardinal, cardinal-open, cardinal-closed, monotone, step-before, step-after), derived_type, interpolation, "linear");
        XPROPERTY(bool, derived_type, close_path, false);
        XPROPERTY(X_CASELESS_STR_ENUM(none, bottom, top, inside), derived_type, fill, "none");
        XPROPERTY(xtl::xoptional<X_CASELESS_STR_ENUM(circle, cross, diamond, square, triangle-down, triangle-up, arrow, rectangle, ellipse)>, derived_type, marker);
        XPROPERTY(int, derived_type, marker_size, 64);
        XPROPERTY(opacities_type, derived_type, opacities);
        XPROPERTY(opacities_type, derived_type, fill_opacities);

    private:

        void set_defaults();
    };

    using lines = xw::xmaterialize<xlines>;

    /*****************************
     * xscatter_base declaration *
     *****************************/

    template <class D>
    class xscatter_base : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;
        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<xtl::xoptional<color_type>>;

        template <class SX, class SY>
        xscatter_base(SX&& sx, SY&& sy);
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(data_type, derived_type, x);
        XPROPERTY(data_type, derived_type, y);
        XPROPERTY(data_type, derived_type, color);
        XPROPERTY(data_type, derived_type, opacity);
        XPROPERTY(data_type, derived_type, size);
        XPROPERTY(data_type, derived_type, rotation);
        XPROPERTY(data_type, derived_type, default_opacities);
        XPROPERTY(::xeus::xjson, derived_type, hovered_style);
        XPROPERTY(::xeus::xjson, derived_type, unhovered_style);
        XPROPERTY(xtl::xoptional<int>, derived_type, hovered_point);
        XPROPERTY(bool, derived_type, enable_move);
        XPROPERTY(bool, derived_type, enable_delete);
        XPROPERTY(bool, derived_type, restrict_x);
        XPROPERTY(bool, derived_type, restrict_y);
        XPROPERTY(bool, derived_type, update_on_move);

    private:

        void set_defaults();
    };

    /************************
     * xscatter declaration *
     ************************/

    template <class D>
    class xscatter : public xscatter_base<D>
    {
    public:

        using base_type = xscatter_base<D>;
        using derived_type = D;
        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<xtl::xoptional<color_type>>;
        using names_type = std::vector<std::string>;

        template <class SX, class SY>
        xscatter(SX&& sx, SY&& sy);
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(data_type, derived_type, skew);
        XPROPERTY(X_CASELESS_STR_ENUM(circle, cross, diamond, square, triangle-down, triangle-up, arrow, rectangle, ellipse), derived_type, marker, "circle");
        XPROPERTY(colors_type, derived_type, colors, {"DeepSkyBlue"});
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);
        XPROPERTY(double, derived_type, stroke_width, 1.5);
        XPROPERTY(double, derived_type, default_skew, 0.5);
        XPROPERTY(int, derived_type, default_size, 64);
        XPROPERTY(names_type, derived_type, names);
        XPROPERTY(bool, derived_type, display_names, true);
        XPROPERTY(bool, derived_type, fill, true);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, drag_color);
        XPROPERTY(double, derived_type, drag_size, 5.);
        XPROPERTY(bool, derived_type, names_unique, true);

    private:

        void set_defaults();
    };

    using scatter = xw::xmaterialize<xscatter>;

    /*********************
    * xhist declaration *
    *********************/

    template<class D>
    class xhist: public xmark<D> 
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;
        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using opacity_type = std::vector<double>;
        
        template <class XS, class YS>
        xhist(XS&&, YS&&);

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);
        
        XPROPERTY(int, derived_type, bins, 10);
        XPROPERTY(colors_type, derived_type, colors);
        XPROPERTY(data_type, derived_type, count);
        XPROPERTY(colors_type, derived_type, midpoints);
        XPROPERTY(bool, derived_type, normalized);
        XPROPERTY(std::vector<double>, derived_type, opacities);
        XPROPERTY(data_type, derived_type, sample);
        XPROPERTY(::xeus::xjson, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);

    private:

        void set_defaults();
    };

    using hist = xw::xmaterialize<xhist>;
    
    /*********************
    * xbars declaration *
    *********************/

    template<class D>
    class xbars: public xmark<D> 
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;
        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using opacity_type = std::vector<double>;

        template <class XS, class YS>
        xbars(XS&&, YS&&);

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(data_type, derived_type, x);
        XPROPERTY(data_type, derived_type, y);
        XPROPERTY(double, derived_type, padding, 0.05);
        XPROPERTY(opacity_type, derived_type, opacities);
        XPROPERTY(colors_type, derived_type, color);
        XPROPERTY(colors_type, derived_type, colors, category10());
        XPROPERTY(::xeus::xjson, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);
        XPROPERTY(X_CASELESS_STR_ENUM(center, left, right), derived_type, align, "center");
        XPROPERTY(X_CASELESS_STR_ENUM(auto, group, element), derived_type, color_mode, "auto");
        XPROPERTY(X_CASELESS_STR_ENUM(vertical, horizontal), derived_type, orientation, "vertical");
        XPROPERTY(X_CASELESS_STR_ENUM(stacked, grouped), derived_type, type, "stacked");

    private:
        
        void set_defaults();
    };

    using bars = xw::xmaterialize<xbars>;

    /************************
     * xmark implementation *
     ************************/

    template <class D>
    inline xmark<D>::xmark()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmark<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(scales, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scales_metadata, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(preserve_domain, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(display_legend, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(labels, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(apply_clip, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(visible, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(selected_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(unselected_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(selected, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(enable_hover, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(interactions, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip_location, patch);
    }

    template <class D>
    inline xeus::xjson xmark<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scales, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scales_metadata, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(preserve_domain, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(display_legend, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(labels, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(apply_clip, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(visible, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(selected_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(unselected_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(selected, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(enable_hover, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(interactions, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip_location, state);

        return state;
    }

    template <class D>
    inline void xmark<D>::set_defaults()
    {
        this->_model_name() = "MarkModel";
    }

    /*************************
     * xlines implementation *
     *************************/

    template <class D>
    template <class SX, class SY>
    inline xlines<D>::xlines(SX&& sx, SY&& sy)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<SX>(sx);
        this->scales()["y"] = std::forward<SY>(sy);
    }

    template <class D>
    inline void xlines<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(y, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(colors, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill_colors, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stroke_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(labels_visibility, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(curves_subset, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(line_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(interpolation, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(close_path, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(marker, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(marker_size, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(opacities, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill_opacities, patch);
    }

    template <class D>
    inline xeus::xjson xlines<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(y, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(colors, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill_colors, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stroke_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(labels_visibility, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(curves_subset, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(line_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(interpolation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(close_path, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(marker, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(marker_size, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(opacities, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill_opacities, state);

        return state;
    }

    template <class D>
    inline void xlines<D>::set_defaults()
    {
        this->_model_name() = "LinesModel";
        this->_view_name() = "Lines";
        this->scales_metadata() = {
            { "x", {{ "orientation", "horizontal" }, { "dimension", "x" }}},
            { "y", {{ "orientation", "vertical" }, { "dimension", "y" }}},
            { "color", {{ "dimension", "color" }}}
        };
    }

    /********************************
     * xscatter_base implementation *
     ********************************/

    template <class D>
    template <class SX, class SY>
    inline xscatter_base<D>::xscatter_base(SX&& sx, SY&& sy)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<SX>(sx);
        this->scales()["y"] = std::forward<SY>(sy);
    }

    template <class D>
    inline void xscatter_base<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(y, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(opacity, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(size, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotation, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(default_opacities, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(hovered_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(unhovered_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(hovered_point, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(enable_move, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(enable_delete, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(restrict_x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(restrict_y, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(update_on_move, patch);
    }

    template <class D>
    inline xeus::xjson xscatter_base<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(y, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(opacity, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(size, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(default_opacities, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(hovered_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(unhovered_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(hovered_point, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(enable_move, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(enable_delete, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(restrict_x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(restrict_y, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(update_on_move, state);

        return state;
    }

    template <class D>
    inline void xscatter_base<D>::set_defaults()
    {
        this->scales_metadata() = { 
            { "x", {{ "orientation", "horizontal" }, { "dimension", "x" }}},
            { "y", {{ "orientation", "vertical" }, { "dimension", "y" }}},
            { "color", {{ "dimension", "color" }}},
            { "size", {{ "dimension", "size" }}},
            { "opacity", {{ "dimension", "opacity" }}},
            { "rotation", {{ "dimension", "rotation" }}}
       };
    }

    /***************************
     * xscatter implementation *
     ***************************/

    template <class D>
    template <class SX, class SY>
    inline xscatter<D>::xscatter(SX&& sx, SY&& sy)
        : base_type(std::forward<SX>(sx), std::forward<SY>(sy))
    {
        set_defaults();
    }

    template <class D>
    inline void xscatter<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(skew, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(marker, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(colors, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stroke, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stroke_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(default_skew, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(default_size, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(names, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(display_names, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fill, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(drag_color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(drag_size, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(names_unique, patch);
    }

    template <class D>
    inline xeus::xjson xscatter<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(skew, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(marker, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(colors, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stroke, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stroke_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(default_skew, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(default_size, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(names, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(display_names, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fill, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(drag_color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(drag_size, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(names_unique, state);

        return state;
    }

    template <class D>
    inline void xscatter<D>::set_defaults()
    {
        this->_model_name() = "ScatterModel";
        this->_view_name() = "Scatter";
    }

    /************************
    * xhist implementation *
    ************************/

    template <class D>
    template <class SX, class SY>
    inline xhist<D>::xhist(SX&& sx, SY&& sy)
        : base_type()
    {
        set_defaults();

        this->scales()["sample"] = std::forward<SX>(sx);
        this->scales()["count"] = std::forward<SY>(sy);
    }

    template <class D>
    inline void xhist<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bins, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(colors, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(count, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(midpoints, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(normalized, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(opacities, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(sample, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scales_metadata, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stroke, patch);
    }

    template <class D>
    inline xeus::xjson xhist<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(bins, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(colors, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(count, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(midpoints, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(normalized, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(opacities, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(sample, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scales_metadata, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stroke, state);

        return state;
    }

    template <class D>
    inline void xhist<D>::set_defaults()
    {
        this->_view_name() = "Hist";
        this->_model_name() = "HistModel";
        this->scales_metadata() = {
            { "sample", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            { "count", {{"orientation", "vertical"}, {"dimension", "y"}}}
        };
    }

    /************************
    * xbars implementation *
    ************************/

    template <class D>
    template <class SX, class SY>
    inline xbars<D>::xbars(SX&& sx, SY&& sy)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<SX>(sx);
        this->scales()["y"] = std::forward<SY>(sy);
    }


    template <class D>
    inline void xbars<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(align, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(color_mode, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(colors, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(opacities, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(padding, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scales_metadata, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stroke, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(type, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(y, patch);
    }

    template <class D>
    inline xeus::xjson xbars<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(align, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(color_mode, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(colors, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(opacities, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(orientation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(padding, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scales_metadata, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stroke, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(type, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(y, state);

        return state;
    }

    template <class D>
    inline void xbars<D>::set_defaults()
    {
        this->_view_name() = "Bars";
        this->_model_name() = "BarsModel";
        this->scales_metadata() = {
            { "x", {{ "orientation", "horizontal" }, { "dimension", "x" }}},
            { "y", {{ "orientation", "vertical" }, { "dimension", "y" }}},
            { "color", {{ "dimension", "color" }}}
        };        
    }    


}

#endif
