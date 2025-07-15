// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PingPongNetClientTarget : TargetRules
{
	public PingPongNetClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange(new string[] { "PingPongNet" });
		
		bUseLoggingInShipping = true;
	}
}
