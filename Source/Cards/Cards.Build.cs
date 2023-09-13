// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cards : ModuleRules
{

	public Cards(ReadOnlyTargetRules Target) : base(Target)
	{
		//string SQLiteSupportPath = "F:/UE4/UE_5.0/Engine/Plugins/Runtime/Database/SQLiteSupport/Source/SQLiteSupport/Public";

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SQLiteSupport", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				ModuleDirectory,
			}
		);
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
