namespace FinancialApp
{
    public class Portfolio
    {
        public Dictionary<string, double> Composition { get; set; }
        public double FreeRateQuantity { get; set; }
        public double FreeRate { get; set; }  
        public Portfolio(Dictionary<string, double> composition, double freeRateQuantity, double freeRate)
        {
            Composition = composition;
            FreeRateQuantity = freeRateQuantity;
            FreeRate = freeRate;
        }
    }
}
