///////////////////////////////////////////////////////////////////////////////
///
/// \file Area.hpp
/// 
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{
class Area;

namespace Events
{
DeclareEvent(AreaChanged);
}

Vec2 ToOffset(Location::Enum origin);
Vec2 OffsetOfOffset(Location::Enum base, Location::Enum corner);

// Thickness used for converting an Area to an Aabb
const float AreaThickness = 0.001f;

/// Sent when an area component's size or origin changes.
class AreaEvent : public Event
{
public:
  ZilchDeclareType(TypeCopyMode::ReferenceType);

  /// The area component that triggered this event.
  Area* mArea;
};

class Area : public Component
{
public:
  ZilchDeclareType(TypeCopyMode::ReferenceType);
  
  //Component Interface
  void Serialize(Serializer& stream) override;
  void Initialize(CogInitializer& initializer) override;
  void SetDefaults() override;
  void DebugDraw() override;

  /// Location of the Origin of the Area
  Location::Enum GetOrigin();
  void SetOrigin(Location::Enum type);

  /// Size of the Area
  Vec2 GetSize();
  void SetSize(Vec2 newSize);

  /// Local space Aabb for the area
  Aabb GetLocalAabb();
  /// World space Aabb for the area
  Aabb GetAabb();

  /// Offset of the given location in local space
  Vec2 LocalOffsetOf(Location::Enum location);
  Vec2 OffsetOfOffset(Location::Enum location);

  #define OffsetOfGetter(location) Vec2 Get##location() { return LocalOffsetOf(Location::location); }
  OffsetOfGetter(TopLeft)
  OffsetOfGetter(TopCenter)
  OffsetOfGetter(TopRight)
  OffsetOfGetter(CenterLeft)
  OffsetOfGetter(Center)
  OffsetOfGetter(CenterRight)
  OffsetOfGetter(BottomLeft)
  OffsetOfGetter(BottomCenter)
  OffsetOfGetter(BottomRight)
  #undef OffsetOfGetter

//Internals
  void DoAreaChanged();
  Vec2 mSize;
  Location::Enum mOrigin;
  Transform* mTransform;
};

}
