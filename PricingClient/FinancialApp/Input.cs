namespace FinancialApp
{
    public class Input
    {
        public string TestParamsPath { get; set; }
        public string MarketDataPath { get; set; }
        public string OutputFilePath { get; set; }
        public Input()
        {
            TestParamsPath = string.Empty;
            MarketDataPath = string.Empty;
            OutputFilePath = string.Empty;
        }
        public Input(string[] args)
        {
            if (args.Length != 3)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Error: 3 parameters are required");
                Console.ResetColor();
                throw new ArgumentException("Error: 3 parameters are required");
            }
            else
            {
                if (args[0].EndsWith(".json"))
                {
                    TestParamsPath = args[0];
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Error: the test-params file should be a JSON file");
                    Console.ResetColor();
                    throw new ArgumentException("Error: the test-params file should be a JSON file");
                }
                if (args[1].EndsWith(".csv"))
                {
                    MarketDataPath = args[1];
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Error: the market-data file should be a CSV file");
                    Console.ResetColor();
                    throw new ArgumentException("Error: the market-data file should be a CSV file");
                }
                if (args[2].EndsWith(".json"))
                {
                    OutputFilePath = args[2];
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Error: the output file should be a JSON file");
                    Console.ResetColor();
                    throw new ArgumentException("Error: the output file should be a JSON file");
                }
            }
        }
    }
}