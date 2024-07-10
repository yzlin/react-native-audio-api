export interface JSIExampleWrapper {
  multiply(a: number, b: number): number;
}

// global func declaration for JSI functions
declare global {
  function nativeCallSyncHook(): unknown;
  var __JSIExampleProxy: JSIExampleWrapper | undefined;
}
