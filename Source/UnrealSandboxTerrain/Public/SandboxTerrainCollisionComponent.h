// Copyright blackw 2015-2020

#pragma once

#include "EngineMinimal.h"
#include "ProceduralMeshComponent.h"

#include "Components/MeshComponent.h"
#include "PhysicsEngine/ConvexElem.h"

#include "SandboxTerrainCollisionComponent.generated.h"


/**
*
*/
UCLASS()
class UNREALSANDBOXTERRAIN_API USandboxTerrainCollisionComponent : public UMeshComponent, public IInterface_CollisionDataProvider 
{
	GENERATED_UCLASS_BODY()

public:

	void ClearMeshSection(int32 SectionIndex);

	void AddCollisionConvexMesh(TArray<FVector> ConvexVerts);

	void ClearCollisionConvexMeshes();

	void SetCollisionConvexMeshes(const TArray< TArray<FVector> >& ConvexMeshes);

	//~ Begin Interface_CollisionDataProvider Interface
	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	virtual bool WantsNegXTriMesh() override { return false; }
	//~ End Interface_CollisionDataProvider Interface


	bool bUseComplexAsSimpleCollision;

	UPROPERTY(Instanced)
	class UBodySetup* ProcMeshBodySetup;

	FProcMeshSection* GetProcMeshSection();

	void SetProcMeshSection(const FProcMeshSection& Section);

	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual class UBodySetup* GetBodySetup() override;
	//~ End UPrimitiveComponent Interface.

	//~ Begin UMeshComponent Interface.
	virtual int32 GetNumMaterials() const override;
	//~ End UMeshComponent Interface.

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface.


private:
	//~ Begin USceneComponent Interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	//~ Begin USceneComponent Interface.


	void UpdateLocalBounds();

	void CreateProcMeshBodySetup();

	void UpdateCollision();

	/** Array of sections of mesh */
	UPROPERTY()
	TArray<FProcMeshSection> ProcMeshSections;

	/** Convex shapes used for simple collision */
	UPROPERTY()
	TArray<FKConvexElem> CollisionConvexElems;

	/** Local space bounds of mesh */
	UPROPERTY()
	FBoxSphereBounds LocalBounds;
};