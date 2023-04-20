#include "pch.h"
#include "MathUtils.h"

bool MathUtils::PointInSphere(const Point3D& point, const Sphere3D sphere)
{
	float magSq = (point - sphere.position).LengthSquared();
	float radSq = sphere.radius * sphere.radius;

	return magSq <= radSq;
}

Point3D MathUtils::ClossestPoint(const Sphere3D& sphere, const Point3D& point)
{
	Vec3 sphereToPointDir = (point - sphere.position);
	sphereToPointDir.Normalize();

	return sphere.position + sphereToPointDir * sphere.radius;
}

bool MathUtils::PointInAABB(const Point3D& point, const AABB3D& aabb)
{
	Point3D min = AABB3D::GetMin(aabb);
	Point3D max = AABB3D::GetMax(aabb);

	if (point.x < min.x || point.y < min.y || point.z < min.z)
		return false;
	if (point.x > max.x || point.y > max.y || point.z > max.z)
		return false;

	return true;
}

Point3D MathUtils::ClosestPoint(const AABB3D& aabb, const Point3D& point)
{
	Point3D result = point;
	Point3D minPt = AABB3D::GetMin(aabb);
	Point3D maxPt = AABB3D::GetMax(aabb);

	result.x = max(result.x, minPt.x);
	result.y = max(result.y, minPt.y);
	result.z = max(result.z, minPt.z);

	result.x = min(result.x, maxPt.x);
	result.y = min(result.y, maxPt.y);
	result.z = min(result.z, maxPt.z);

	return result;
}

// OBB������ �� ������ point�� �����ϴ� ���
bool MathUtils::PointInOBB(const Point3D& point, const OBB3D& obb)
{
	Vec3 dir = point - obb.position;

	vector<Vec3> axis;
	axis.push_back(obb.orientation.Right());
	axis.push_back(obb.orientation.Up());
	axis.push_back(obb.orientation.Backward());

	vector<float> size;
	size.push_back(obb.size.x);
	size.push_back(obb.size.y);
	size.push_back(obb.size.z);

	for (int32 i = 0; i < 3; i++)
	{
		float distance = dir.Dot(axis[i]);

		if (distance > size[i])
			return false;
		if (distance < -size[i])
			return false;
	}

	return true;
}

Point3D MathUtils::ClosestPoint(const OBB3D& obb, const Point3D& point)
{
	Point3D result = obb.position;
	Vec3 dir = point - obb.position;

	vector<Vec3> axis;
	axis.push_back(obb.orientation.Right());
	axis.push_back(obb.orientation.Up());
	axis.push_back(obb.orientation.Backward());

	vector<float> size;
	size.push_back(obb.size.x);
	size.push_back(obb.size.y);
	size.push_back(obb.size.z);

	for (int i = 0; i < 3; ++i)
	{
		float distance = dir.Dot(axis[i]);

		if (distance > size[i])
			distance = size[i];

		if (distance < -size[i])
			distance = -size[i];

		result = result + (axis[i] * distance);
	}

	return result;
}

bool MathUtils::PointOnPlane(const Point3D& point, const Plane3D& plane)
{
	float dot = point.Dot(plane.normal);
	// CMP(dot - plane.distance, 0.0f);
	return dot == plane.distance;
}

Point3D MathUtils::ClosestPoint(const Plane3D& plane, const Point3D& point)
{
	float dot = point.Dot(plane.normal);
	float distance = dot - plane.distance;
	return point - plane.normal * distance;
}

Point3D MathUtils::ClosestPoint(const Line3D& line, const Point3D& point)
{
	Vec3 lVec = line.end - line.start; // Line Vector
	float t = (point - line.start).Dot(lVec) / lVec.Dot(lVec);
	t = fmaxf(t, 0.0f); // Clamp to 0
	t = fminf(t, 1.0f); // Clamp to 1
	return line.start + lVec * t;
}

bool MathUtils::PointOnLine(const Point3D& point, const Line3D& line)
{
	Point3D closest = ClosestPoint(line, point);
	float distanceSq = (closest - point).LengthSquared();
	// CMP(distanceSq, 0.0f);
	return distanceSq == 0.f;
}

bool MathUtils::PointOnRay(const Point3D& point, const Ray3D& ray)
{
	if (point == ray.origin)
		return true;

	Vec3 norm = point - ray.origin;
	norm.Normalize();

	float diff = norm.Dot(ray.direction);
	return diff == 1.0f; // Consider using epsilon!
}

Point3D MathUtils::ClosestPoint(const Ray3D& ray, const Point3D& point)
{
	float t = (point - ray.origin).Dot(ray.direction);

	t = fmaxf(t, 0.0f);

	return Point3D(ray.origin + ray.direction * t);
}

bool MathUtils::SphereSphere(const Sphere3D& s1, const Sphere3D& s2)
{
	float sum = s1.radius + s2.radius;
	float sqDistance = (s1.position - s2.position).LengthSquared();
	return sqDistance <= sum * sum;
}

bool MathUtils::SphereAABB(const Sphere3D& sphere, const AABB3D& aabb)
{
	Point3D closestPoint = ClosestPoint(aabb, sphere.position);
	float distSq = (sphere.position - closestPoint).LengthSquared();
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool MathUtils::SphereOBB(const Sphere3D& sphere, const OBB3D& obb)
{
	Point3D closestPoint = ClosestPoint(obb, sphere.position);
	float distSq = (sphere.position - closestPoint).LengthSquared();
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool MathUtils::SpherePlane(const Sphere3D& sphere, const Plane3D& plane)
{
	Point3D closestPoint = ClosestPoint(plane, sphere.position);
	float distSq = (sphere.position - closestPoint).LengthSquared();
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool MathUtils::AABBAABB(const AABB3D& aabb1, const AABB3D& aabb2)
{
	Point3D aMin = AABB3D::GetMin(aabb1);
	Point3D aMax = AABB3D::GetMax(aabb1);
	Point3D bMin = AABB3D::GetMin(aabb2);
	Point3D bMax = AABB3D::GetMax(aabb2);

	return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
		(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
		(aMin.z <= bMax.z && aMax.z >= bMin.z);
}

Interval3D MathUtils::GetInterval(const AABB3D& aabb, const Vec3& axis)
{
	Vec3 i = AABB3D::GetMin(aabb);
	Vec3 a = AABB3D::GetMax(aabb);

	Vec3 vertex[8] =
	{
		Vec3(i.x, a.y, a.z),
		Vec3(i.x, a.y, i.z),
		Vec3(i.x, i.y, a.z),
		Vec3(i.x, i.y, i.z),
		Vec3(a.x, a.y, a.z),
		Vec3(a.x, a.y, i.z),
		Vec3(a.x, i.y, a.z),
		Vec3(a.x, i.y, i.z)
	};

	// �ּ�/�ִ� ���ϱ�
	Interval3D result;
	result.min = result.max = axis.Dot(vertex[0]);

	for (int i = 1; i < 8; ++i)
	{
		float projection = axis.Dot(vertex[i]);
		result.min = min(result.min, projection);
		result.max = max(result.max, projection);
	}

	return result;
}

Interval3D MathUtils::GetInterval(const OBB3D& obb, const Vec3& axis)
{
	Vec3 vertex[8];

	Vec3 C = obb.position; // OBB Center
	Vec3 E = obb.size; // OBB Extents

	vector<Vec3> A; // OBB Axis
	A.push_back(obb.orientation.Right());
	A.push_back(obb.orientation.Up());
	A.push_back(obb.orientation.Backward());

	// �� ��ǥ�� �����ش�
	vertex[0] = C + A[0] * E.x + A[1] * E.y + A[2] * E.z;
	vertex[1] = C - A[0] * E.x + A[1] * E.y + A[2] * E.z;
	vertex[2] = C + A[0] * E.x - A[1] * E.y + A[2] * E.z;
	vertex[3] = C + A[0] * E.x + A[1] * E.y - A[2] * E.z;
	vertex[4] = C - A[0] * E.x - A[1] * E.y - A[2] * E.z;
	vertex[5] = C + A[0] * E.x - A[1] * E.y - A[2] * E.z;
	vertex[6] = C - A[0] * E.x + A[1] * E.y - A[2] * E.z;
	vertex[7] = C - A[0] * E.x - A[1] * E.y + A[2] * E.z;

	// �ּ�/�ִ� ���ϱ�
	Interval3D result;
	result.min = result.max = axis.Dot(vertex[0]);

	for (int i = 1; i < 8; ++i)
	{
		float projection = axis.Dot(vertex[i]);
		result.min = min(result.min, projection);
		result.max = max(result.max, projection);
	}

	return result;
}

bool MathUtils::OverlapOnAxis(const AABB3D& aabb, const OBB3D& obb, const Vec3& axis)
{
	Interval3D a = GetInterval(aabb, axis);
	Interval3D b = GetInterval(obb, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool MathUtils::AABBOBB(const AABB3D& aabb, const OBB3D& obb)
{
	Vec3 test[15] =
	{
		Vec3(1, 0, 0),				// AABB axis 1
		Vec3(0, 1, 0),				// AABB axis 2
		Vec3(0, 0, 1),				// AABB axis 3
		obb.orientation.Right(),	// OBB axis 1
		obb.orientation.Up(),		// OBB axis 2
		obb.orientation.Backward()  // OBB axis 3
		// We will fill out the remaining axis in the next step
	};

	for (int i = 0; i < 3; ++i)
	{
		// Fill out rest of axis
		test[6 + i * 3 + 0] = test[i].Cross(test[0]);
		test[6 + i * 3 + 1] = test[i].Cross(test[1]);
		test[6 + i * 3 + 2] = test[i].Cross(test[2]);
	}

	for (int i = 0; i < 15; ++i)
	{
		if (OverlapOnAxis(aabb, obb, test[i]) == false)
			return false; // Seperating axis found
	}

	return true; // Seperating axis not found
}

bool MathUtils::AABBPlane(const AABB3D& aabb, const Plane3D& plane)
{
	float pLen = aabb.size.x * fabsf(plane.normal.x) +
		aabb.size.y * fabsf(plane.normal.y) +
		aabb.size.z * fabsf(plane.normal.z);

	float dot = plane.normal.Dot (aabb.position);
	float dist = dot - plane.distance;

	return fabsf(dist) <= pLen;
}

bool MathUtils::OverlapOnAxis(const OBB3D& obb1, const OBB3D& obb2, const Vec3& axis)
{
	Interval3D a = GetInterval(obb1, axis);
	Interval3D b = GetInterval(obb1, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool MathUtils::OBBOBB(const OBB3D& obb1, const OBB3D& obb2)
{
	Vec3 test[15] =
	{
		obb1.orientation.Right(),
		obb1.orientation.Up(),
		obb1.orientation.Backward(),
		obb2.orientation.Right(),
		obb2.orientation.Up(),
		obb2.orientation.Backward(),
	};

	for (int i = 0; i < 3; ++i)
	{
		// Fill out rest of axis
		test[6 + i * 3 + 0] = test[i].Cross(test[0]);
		test[6 + i * 3 + 1] = test[i].Cross(test[1]);
		test[6 + i * 3 + 2] = test[i].Cross(test[2]);
	}

	for (int i = 0; i < 15; ++i)
	{
		if (OverlapOnAxis(obb1, obb2, test[i]) == false)
			return false; // Seperating axis found
	}

	return true; // Seperating axis not found
}

bool MathUtils::PlanePlane(const Plane3D& plane1, const Plane3D& plane2)
{
	Vec3 d = plane1.normal.Cross(plane2.normal);
	return d.Dot(d) != 0; // Consider using an epsilon!
}








