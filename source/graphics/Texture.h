#pragma once

#include <glm/glm.hpp>

#include "core/Object.h"

class Image;

class Texture : public Object
{
   public:
    Texture(Image* image = nullptr);
    virtual ~Texture() = default;

    void setImage(Pointer<Image> image);
    Pointer<Image> getImage();

    // Type of proejction used when drawing
    enum class Correction
    {
        Affine,
        Perspective,

        Max
    };
    Correction correction = Correction::Perspective;

    // Texture filtering mode
    enum class Filter
    {
        Nearest,
        Linear,

        Max
    };
    Filter filter = Filter::Linear;

    // Mip mapping mode
    enum class MipMap
    {
        Nearest,
        Linear,
        NearestNearest,
        NearestLinear,
        LinearNearest,
        LinearLinear,

        Max
    };
    MipMap mipMap = MipMap::LinearLinear;

    // Out of range coordinate mode
    enum class Coordinate
    {
        Clamp,
        Repeat,
        ClampBorder,
        ClampEdge,

        Max
    };
    Coordinate coordU = Coordinate::ClampEdge;
    Coordinate coordV = Coordinate::ClampEdge;
    glm::vec4 borderColor = glm::vec4{0.f, 0.f, 0.f, 1.f};

    // Texture coordinate generation mode
    enum class TexGen
    {
        None,
        EnvironmentMap,
        ProjectedTexture,

        Max
    };
    TexGen texGen = TexGen::None;

    // Application mode
    enum class Apply
    {
        Replace,
        Decal,
        Modulate,
        Blend,
        Add,
        Combine,

        Max
    };
    Apply apply = Apply::Replace;

    glm::vec4 blendColor = glm::vec4{0.f, 0.f, 0.f, 1.f};

    /**
     * For mutitexturing with apply mode Apply::Combine
     */
    enum class ApplyCombineFunc
    {
        Replace,
        Modulate,
        Add,
        AddSigned,
        Subtract,
        Interpolate,
        Dot3RGB,
        Dot3RGBA,

        Max
    };
    ApplyCombineFunc combineFuncRGB = ApplyCombineFunc::Replace;
    ApplyCombineFunc combineFuncAlpha = ApplyCombineFunc::Replace;

    enum class ApplyCombineSrc
    {
        Texture,
        PrimaryColor,
        Constant,
        Previous,

        Max
    };
    ApplyCombineSrc combineSrc0RGB = ApplyCombineSrc::Texture;
    ApplyCombineSrc combineSrc1RGB = ApplyCombineSrc::Texture;
    ApplyCombineSrc combineSrc2RGB = ApplyCombineSrc::Texture;
    ApplyCombineSrc combineSrc0Alpha = ApplyCombineSrc::Texture;
    ApplyCombineSrc combineSrc1Alpha = ApplyCombineSrc::Texture;
    ApplyCombineSrc combineSrc2Alpha = ApplyCombineSrc::Texture;

    enum class ApplyCombineOperand
    {
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,

        Max
    };
    ApplyCombineOperand combineOp0RGB = ApplyCombineOperand::SrcColor;
    ApplyCombineOperand combineOp1RGB = ApplyCombineOperand::SrcColor;
    ApplyCombineOperand combineOp2RGB = ApplyCombineOperand::SrcColor;
    ApplyCombineOperand combineOp0Alpha = ApplyCombineOperand::SrcColor;
    ApplyCombineOperand combineOp1Alpha = ApplyCombineOperand::SrcColor;
    ApplyCombineOperand combineOp2Alpha = ApplyCombineOperand::SrcColor;

    enum class ApplyCombineScale
    {
        One,
        Two,
        Four,

        Max
    };
    ApplyCombineScale combineScaleRGB = ApplyCombineScale::One;
    ApplyCombineScale combineScaleAlpha = ApplyCombineScale::One;

   protected:
    Pointer<Image> m_image;
};