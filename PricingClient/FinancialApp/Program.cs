class Program
{
    static async Task Main(string[] args)
    {
        
        string serverAddress = "http://localhost:50051";
        var heartbeatInfo = await GrpcClientUtil.GetHeartbeatInfoAsync(serverAddress);
        Console.WriteLine("g réussiiiii");
        if (heartbeatInfo != null)
        {
            Console.WriteLine($"Domestic Interest Rate: {heartbeatInfo.DomesticInterestRate}");
            Console.WriteLine($"Relative Finite Difference Step: {heartbeatInfo.RelativeFiniteDifferenceStep}");
            Console.WriteLine($"Sample Number: {heartbeatInfo.SampleNb}");
        }
        else
        {
            Console.WriteLine("Failed to retrieve heartbeat information.");
        }

        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }
}